/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:07:06 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/25 11:50:23 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *heredocinput(char *delimiter)
{
	char *docarg;
	char *input = ft_strdup("");
    while((docarg = readline("heredoc> ")) != NULL)
        {
			
			if (!ft_strncmp(docarg, delimiter, ft_strlen(delimiter)))
				return(input);			
			input = ft_strjoin(input, docarg);
            input = ft_strjoin(input, "\n");
        }
    return(input);
}

void print_tokenlist(t_token *token_list)
{
	while(token_list)
	{
		printf("%s\n", token_list->str);
		token_list = token_list->next;
	}
}

t_expression	*parse_pipe(t_token **token_list, t_expression *node, char *path)
{
	t_expression	*pipe;
	t_expression	*right;

	if (!(*token_list) || (*token_list)->token_type != PIPE)
		return (node);
	
	*token_list = (*token_list)->next;
	right = val_pars(token_list, path);
	pipe = malloc(sizeof(t_expression));
	if (!pipe)
		exit(1);
	pipe->left = node;
	pipe->right = right;
	return(pipe);
}

t_expression	*val_pars(t_token **token_list, char *path)
{
	t_expression	*cmdparse;
	t_variables		*assignment;

	assignment = NULL;
	cmdparse = malloc(sizeof(t_expression));
	if (!cmdparse)
		exit(1);
	cmdparse->left = NULL;
	cmdparse->right = NULL;
	cmdparse->red = extr_pars_red(*token_list);
	//printf("token at the start: %s\n", (*token_list)->str);
	
	(*token_list) = parse_assign(*token_list, &assignment);
	//printf("token advanced after parse_assign: %s\n", (*token_list)->str);

	(*token_list) = parse_command(*token_list, &cmdparse, &assignment, path);
	//printf("token advanced after parse_command: %s\n", (*token_list)->str);

	(*token_list) = parse_arg(*token_list, &cmdparse);
	//printf("token advanced after parse_arg: %s\n", (*token_list)->str);

	(*token_list) = val_pars_recursion(&cmdparse, *token_list, path);
	//printf("token advanced after parse_recursion: %s\n", (*token_list)->str);

	if ((*token_list)->token_type == PIPE)
	{
		cmdparse = parse_pipe(token_list, cmdparse, path);
	}

	printf("cmdparse type = %s\n", cmdparse->value);
	return (cmdparse);
}








