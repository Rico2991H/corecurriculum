/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:39:23 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/10 11:47:31 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	traverse_arguments(t_expression *cmd_parse)
{
	t_arg   *arg_trav;
	t_variables *ass_trav;

	ass_trav = cmd_parse->assignment;
	arg_trav = cmd_parse->args;
	while(arg_trav)
	{
		if(arg_trav->arg[0] == '$' && arg_trav->s_quote == 0)
		{
			if (!ft_strncmp(ass_trav->name,
				&arg_trav->arg[1], ft_strlen(ass_trav->name)))
			{
				arg_trav->arg = ass_trav->value;
			}
		}
		arg_trav = arg_trav->next;
	}
}

char	*create_buf(t_redirection *red_trav, int *i, int *j)
{
	char *buf;

	buf = malloc(sizeof(char) * *i);
	while(*j < *i)
	{
		buf[*j] = red_trav->hdinput[*j];
		(*j)++; 
	}
	buf[*j] = '\0'; //not sure if necessary
	while(red_trav->hdinput[*j] > 32)
		(*j)++;
	return(buf);
}

void	replace_hdinput(t_redirection *red_trav, t_variables *ass_trav, int i)
{
	int j;
	int	len;
	char *buf;
	char *new_input;

	j = 0;
	buf = create_buf(red_trav, &i, &j);
	new_input = ft_strjoin(buf, ass_trav->value);
	len = j;
	while(red_trav->hdinput[len])
		len++;
	len = len - j;
	buf = malloc(sizeof(char) * len);
	len = j;
	j = 0;
	while(red_trav->hdinput[len])
	{
		buf[j] = red_trav->hdinput[len];
		j++;
		len++;
	}
	new_input = ft_strjoin(new_input, buf);
	free(red_trav->hdinput);
	free(buf);
	red_trav->hdinput = new_input;
}


void	traverse_redirection(t_expression *cmd_parse)
{
	t_redirection	*red_trav;
	t_variables		*ass_trav;
	int				i;
	
	i = 0;
	red_trav = cmd_parse->red;
	ass_trav = cmd_parse->assignment;
	
	while(red_trav)
	{
		if(red_trav->Type == HEREDOC)
		{
			while(red_trav->hdinput[i])
			{
				if(red_trav->hdinput[i] == '$' && red_trav->s_quote == 0)
				{
					replace_hdinput(red_trav, ass_trav, i);
					i = -1;
				}
				i++;
			}
		}
		printf("hdinput = %s\n", red_trav->hdinput);
		red_trav = red_trav->next;
	}
}

void    compare_words(t_expression *cmd_parse)
{
	traverse_arguments(cmd_parse);
	traverse_redirection(cmd_parse);
}

void    expansion_checker(t_expression *cmd_parse)
{
	if(cmd_parse == NULL) // must set last node to NULL in earlier recursive function.
		return;
	if (cmd_parse->Type == NODE_COMMAND)
	{
		compare_words(cmd_parse);
		expansion_checker(cmd_parse->left);
		expansion_checker(cmd_parse->right);
	}
	if (cmd_parse->Type == NODE_ASSIGNMENT)
		return;
	if (cmd_parse->Type == NODE_AND)
	{
		expansion_checker(cmd_parse->left);
		expansion_checker(cmd_parse->right);
	}
	if (cmd_parse->Type == NODE_OR)
	{
		expansion_checker(cmd_parse->left);
		expansion_checker(cmd_parse->right);
	}
	if (cmd_parse->Type == NODE_PIPE)
	{
		expansion_checker(cmd_parse->left);
		expansion_checker(cmd_parse->right);
	}
}

