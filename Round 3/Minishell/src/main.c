/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:39:49 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/26 12:09:35 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void	free_tokens(t_token *token_list)
{
	t_token *temp;

	while(token_list)
	{
		temp = token_list;
		token_list = token_list->next;
		free(temp);
	}
}

char	*getpath(char **envp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (envp [i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	printf("found PATH\n");
	if (!envp[i])
		return (NULL);
	return (ft_strdup(&envp[i][j + 5]));
}

t_token	*prepend_node(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->token_type = 0;
	new->s_quote = 0;
	new->d_quote = 0;
	new->next = token;
	return (new);
}

t_token	*create_list(int i)
{
	int	j;
	t_token	*token;
	
	j = 0;
	token = NULL;
	while(j < i)
	{
		token = prepend_node(token);
		if (!token)
		{
			free(token);
			return (NULL);
		}
		j++;
	}
	return (token);
}

/*static void	print_tree(t_expression *tree, int depth)
{
	if (!tree) 
		return;
	for (int i = 0; i < depth; i++) printf("  ");
	if (tree->Type == NODE_SUBSHELL)
	{
		printf("node_subshell\n");
		return ;
	}
	printf("%s (%s)\n", tree->value, tree->Type == NODE_PIPE ? "PIPE" : (tree->Type == NODE_COMMAND ? "CMD" : "OP"));
	print_tree(tree->left, depth + 1);
	print_tree(tree->right, depth + 1);
}*/


int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)**argv;
	char *input;
	char *path;
	int i;
	t_env	*env;
	t_token	*token_node;
	t_expression *parse_cmds;
	t_variables *assignmentlist;

	assignmentlist = NULL;
	env = copy_env(envp);
	signal_set();
	while((input = readline("Minishell ")) != NULL)
	{
		history(input);
		i = token_counter(input);
		token_node = create_list(i);
		if (!token_node)
			return (1);
		path = getpath(envp);
		printf("got path safely\n");
		tokenizer(token_node, input);
		printf("got tokens safely\n");
		parse_cmds = recursion(&token_node, path);
		printf("going into expansion\n");
		expansion_checker(parse_cmds, assignmentlist);
		free(path);
		printf("entering priority\n");
		i = priority(parse_cmds, &env, &assignmentlist, envp);
		printf("exit status is %d\n", i);
		printf("entering free\n");
		free_tokens(token_node);
		//print_tree(parse_cmds, 0);
	}
	//rl_clear_history();
}


