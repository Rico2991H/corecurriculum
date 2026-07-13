/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:39:23 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/13 11:49:05 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_buf(char *str, int *i, int *j)
{
	char	*buf;
	int		var_len;

	var_len = 0;
	buf = malloc(sizeof(char) * (*i + 1));
	if (!buf)
		return (NULL);
	while (*j < *i)
	{
		buf[*j] = str[*j];
		(*j)++; 
	}
	buf[*j] = '\0';
	(*j)++;
	var_len = find_varname(&str[*j]);
	(*j) += var_len;
	return (buf);
}

void	replace_hdinput(t_redirection *red_trav, t_variables *ass_trav, int i)
{
	int		j;
	char	*buf;
	char	*new_input;
	char	*new_input2;

	j = 0;
	buf = create_buf(red_trav->hdinput, &i, &j);
	if (!buf)
		return ;
	new_input = ft_strjoin(buf, ass_trav->value);
	free(buf);
	new_input2 = ft_strjoin(new_input, red_trav->hdinput + j);
	free(red_trav->hdinput);
	free(new_input);
	red_trav->hdinput = new_input2;
}

void	compare_words(t_expression *cmd_parse, t_variables *assignments, int e)
{
	quote_cleaner(cmd_parse, assignments, e);
	check_for_ast(cmd_parse);
	if (cmd_parse->red && cmd_parse->red->type != HEREDOC)
	{
		check_for_ast_red(cmd_parse);
		remove_ast_red(&cmd_parse->red);
	}
	remove_ast(&cmd_parse->args);
}

void	expansion_checker(t_expression *cmd_parse, 
		t_variables *assignments, int e)
{
	if (cmd_parse == NULL)
		return ;
	if (cmd_parse->type == NODE_COMMAND)
		compare_words(cmd_parse, assignments, e);
	expansion_checker(cmd_parse->left, assignments, e);
	expansion_checker(cmd_parse->right, assignments, e);
	expansion_checker(cmd_parse->child, assignments, e);
}
