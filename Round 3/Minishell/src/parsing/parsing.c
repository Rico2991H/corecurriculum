/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:07:06 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/10 11:42:34 by rhoogend         ###   ########.fr       */
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

t_expression	*val_pars(t_token **token_list, char *path)
{
	t_expression	*cmdparse;
	t_variables		*assignment;

	assignment = NULL;
	cmdparse = malloc(sizeof(t_expression));
	cmdparse->left = NULL;
	cmdparse->right = NULL;
	if (!cmdparse)
		exit(1);
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

	return (cmdparse);
}








