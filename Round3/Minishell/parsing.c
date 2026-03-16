/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:07:06 by rhoogend          #+#    #+#             */
/*   Updated: 2025/10/27 14:04:09 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *heredocinput(char *delimiter)
{
	char *docarg;
	char *input = ft_strdup("");
    while((docarg = readline("heredoc> ")) != NULL && ft_strncmp(docarg, delimiter, ft_strlen(delimiter)))
        {	        
			input = ft_strjoin(input, docarg);
            input = ft_strjoin(input, "\n");
        }
    return(input);
}

int	find_equals(t_token *token)
{	
	if (!ft_strnstr(token->str, "=", ft_strlen(token->str)))
		return (0);
	return(1);
}


int	check_for_operator(char *str)
{
	if (!ft_strncmp("&&", str, 2))
		return(2);
	if (!ft_strncmp("||", str, 2))
		return(3);
	if (!ft_strncmp("|", str, 1))
		return(1);
	return (0); 
}

void	create_assign(t_token *token_list, t_variables **assignment)
{
	char	**key_val;
	
		t_variables *temp;
		t_variables *new_assignment;

		temp = *assignment;
		new_assignment = malloc(sizeof(t_variables));
		if (!new_assignment)
			return;
		key_val = ft_split(token_list->str, *ft_strdup("="));
		new_assignment->name = key_val[0];
		new_assignment->value = key_val[1];
		new_assignment->next = NULL;
		free(key_val);
		if (*assignment == NULL)
			*assignment = new_assignment;
		else
		{
		while (temp->next)
			temp = temp->next;
		temp->next = new_assignment;
		}
}

t_token	*parse_arg(t_token *token_list, t_expression **cmd_parse)
{	
	char	**arg;
	int		i;
	t_token *temp;

	i = 0;
	temp = token_list;
	while(temp && temp->token_type == STRING)
	{
		i++;
		temp = temp->next;
	}
	arg = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(token_list && token_list->token_type == STRING)
	{
		arg[i] = token_list->str;
		i++;
		token_list = token_list->next;
	}
	(*cmd_parse)->arg = arg;
	return(token_list);
}

t_redirection	*new_node_red(t_redirection **node)
{
		t_redirection *temp;
		t_redirection *new_node;

		temp = *node;
		new_node = malloc(sizeof(t_redirection));
		if (!new_node)
			return(NULL);
		new_node->name = NULL;
		new_node->arrow = NULL;
		new_node->next = NULL;
		if (*node == NULL)
			return(new_node);
		else
		{
			while (temp->next)
				temp = temp->next;
			temp->next = new_node;
			return(temp->next);
		}
}
/*
	if (token_list->token_type == REDIRECT)
		{
			if (!ft_strncmp(&token_list->str, "<<", 2))
*/
void	assign_red(t_token *token_list, t_redirection **current)
{
	t_token *temp1;
	t_redirection *extract;
	
	temp1 = token_list;
	extract = NULL;
	while(temp1) //Something
	{
		if (temp1->token_type == REDIRECT)
		{
			*current = new_node_red(&extract);
			(*current)->arrow = temp1->str;
			//if(ft_strncmp(current->arrow, "<<", 2))
			//	current->hdinput = heredocinput(temp1->next->str);
			temp1 = temp1->next;
			if (!temp1)
				break;
			(*current)->name = temp1->str;
			temp1 = temp1->next;
		}
		else
			temp1 = temp1->next;
	}	
}

t_redirection 	*extr_pars_red(t_token *token_list)
{
	t_redirection *current;
	t_token *temp2;
	t_token *temp3;

	temp2 = token_list;
	current = NULL;
	assign_red(token_list, &current);
	while(temp2 && temp2->next)
	{
		if (temp2->next->token_type == REDIRECT)
		{
			temp3 = temp2->next;
			temp2->next = temp3->next->next;
			free(temp3->next);
			free(temp3);	
		}
		else
			temp2 = temp2->next;
	}
	return (current);
}

t_token	*parse_assign(t_token *token_list, t_variables **assignment)
{
	while(token_list && token_list->token_type == STRING && find_equals(token_list))
	{
		create_assign(token_list, assignment);
		token_list = token_list->next;
	}
	return(token_list);
}
int 	find_command(char *command, t_expression **cmdparse)
{
	char	*slashed_cmd;
	char	*path_cmd;
	int		i;
	
	i = 0;
	slashed_cmd = ft_strjoin("/", command);
	while((*cmdparse)->split_paths[++i])
	{
		path_cmd = ft_strjoin((*cmdparse)->split_paths[i], slashed_cmd);
		if(!path_cmd)
		{
			//something error
			return(0);
		}
		if(access(path_cmd, F_OK) == 0)
			return(1);
	}
	return(0);
}
t_token	*parse_command(t_token *token_list, t_expression **cmdparse, t_variables **assignment)
{
	if(token_list->token_type == STRING && find_command(token_list->str, cmdparse))
	{
		(*cmdparse)->Type = NODE_COMMAND;
		(*cmdparse)->value = token_list->str;
		(*cmdparse)->assignment = *assignment;
		token_list = token_list->next;
	}
	return(token_list);
}
void	pars_operator(t_token *token_list, t_expression **cmdparse, char *path)
{
	int	operator;
	(void)path;
	operator = check_for_operator(token_list->str);
	if (operator)
	{
		t_expression	*op_parse;
		op_parse = malloc(sizeof(t_expression));
		op_parse->value = token_list->str;
		op_parse->Type = operator;
		op_parse->left = *cmdparse;
		printf("left of parse %s\n", op_parse->left->value);
		//val_pars(token_list->next->next, path);
	}
}
void print_tokenlist(t_token *token_list)
{
	while(token_list)
	{
		printf("%s\n", token_list->str);
		token_list = token_list->next;
	}
}

void 	val_pars(t_token *token_list, char *path) 
{
	t_expression	*cmdparse;
	t_variables *assignment;

	assignment = NULL;
	cmdparse = malloc(sizeof(t_expression));
	cmdparse->split_paths = ft_split(path, ':');
	if (!cmdparse->split_paths)
	{
		perror("split_paths failed");
		free(path);
	}
	cmdparse->red = extr_pars_red(token_list);
	token_list = parse_assign(token_list, &assignment);
	token_list = parse_command(token_list, &cmdparse, &assignment);
	token_list = parse_arg(token_list, &cmdparse);
	pars_operator(token_list, &cmdparse, path);
}



