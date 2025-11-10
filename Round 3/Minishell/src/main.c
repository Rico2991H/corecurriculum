/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:39:49 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/10 09:30:00 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	assign_array(t_token *token_node, int i)
{
	int j;

	j = 0;
	while(j != i)
	{
		token_node[j].operators = NULL;
		token_node[j].parent = NULL;
		token_node[j].redirect = NULL;
		token_node[j].string = NULL;
		j++;
	}
}*/

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

static void	print_tree(t_expression *tree, int depth)
{
	if (!tree) 
		return;
	for (int i = 0; i < depth; i++) printf("  ");
	if (tree->Type == NODE_SUBSHELL)
	{
		printf("node_subshell\n");
		return ;
	}
	printf("%s (%s)\n", tree->value, tree->Type == NODE_COMMAND ? "CMD" : "OP");
	print_tree(tree->left, depth + 1);
	print_tree(tree->right, depth + 1);
}


int main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)**argv;
	(void)**envp;
	char *input;
	char *path;
	int i;
	t_token	*token_node;
	t_expression *parse_cmds;

	signal_set();
	while((input = readline("Minishell ")) != NULL)
	{
		history(input);
		i = token_counter(input);
		printf("token counter succes %d amount of tokens\n", i);
		token_node = create_list(i);
		if (!token_node)
			return (1);
		printf("malloc successful\n");
		path = getpath(envp);
		printf("got path safely\n");
		tokenizer(token_node, input);
		printf("got tokens safely\n");
		parse_cmds = recursion(&token_node, path);
		printf("going into expansion\n");
		expansion_checker(parse_cmds);
		free(path);
		free_tokens(token_node);
		print_tree(parse_cmds, 0);
	}
	//rl_clear_history();
}


















































/*Create struct containing 1 token per struct item 
store items in array containing those structs.
The array will contain structs and serve as an index.


If you want to index tokens, put the structs into an array (static or dynamic).

Then use normal array indexing (tokens[i]) to access them in order.*/

/*

int tokenizer(char *arg)
{
	int i = 0
		while(arg)
	{
		if (arg[i] == "(")
			check_for_group;
		if (arg[i] == "\"")
			check_for_command
			//check_for_string;
		if (arg[i] == (a letter or number))
			check_for_command
		i++;
	}
}

int	check_for_group(char *arg, int i)
{
	int j = i;
	while(arg || arg[i] != ")")
	{
		if (arg[j] == ")")
			//add_to_group
		if (!check_for_group);
		{
			if (!check_for_command);
			{
				if (!check_for_string);
					return;
			}
		}
		check_for_operator;
	}
}

void  check_for_command(char *arg, int i)
{
	int j = i;
	while(arg != ' ')
	{
		if (arg[j]) == (matching command)
			j++;
		if (arg[j]) != (matching command)
		{
			check_for_string(char *arg, int i)
			return;
		}
		j++;
	}
	//add_to_command() or is_command() or perhaps check_for_expression() since this will evaluate to a value we can record. 
}

	if (arg == ' ')
	{
		j++;
		if (!check_for_keyword()
		{
			if (!check_for_string())
				return;
		}
		else
		{
			check_for_string()
		}
	}
	
}

int check_for_string(char *arg, int i)
{
	int j = i;
	if arg[i] == "\""
	{
		j++;
		while (arg || arg[j] != "\"")
		{
			if (arg == "\"")
				add_to_string() // or something like that in t			if (arg[i]) == strcmp(command)
				token->command == arg[i] until j;
			else
				token->string == arg[i] until j he end everything needs to be turned into expressions id say.... so just a string is potentially useless.
			j++:
		}
	else
	{
		while (arg != " ")
			j++:
		add_to_string()
	}
}*/ 
