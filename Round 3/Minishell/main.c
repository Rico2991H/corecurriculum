/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:39:49 by rhoogend          #+#    #+#             */
/*   Updated: 2025/10/27 15:22:59 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*void	assign_array(t_token *array_of_tokens, int i)
{
	int j;

	j = 0;
	while(j != i)
	{
		array_of_tokens[j].operators = NULL;
		array_of_tokens[j].parent = NULL;
		array_of_tokens[j].redirect = NULL;
		array_of_tokens[j].string = NULL;
		j++;
	}
}*/
char	*getpath(char **envp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (envp [i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
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
int main(int argc, char *argv[], char **envp) //char **envp
{
	(void)argc;
	(void)**argv;
	char *input;
	char *path;
	int i;
	//int j;
	t_token *token_node;

	signal_set();
	while((input = readline("Minishell ")) != NULL)
	{
		history(input);
		i = token_counter(input);
		token_node = create_list(i);
		if(!token_node)
			return (1);
		path = getpath(envp);
		tokenizer(token_node, input);
		val_pars(token_node, path);
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
