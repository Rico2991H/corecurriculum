/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:33:29 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/12 17:13:03 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_operator(char *str)
{
	if (!ft_strncmp("&&", str, 2))
		return (2);
	if (!ft_strncmp("||", str, 2))
		return (3);
	if (!ft_strncmp("|", str, 1))
		return (1);
	return (0); 
}

static void	fill_val_opparse(t_expression **op_parse, 
							int operator, t_token *token_list)
{
	(*op_parse)->value = ft_strdup(token_list->str);
	(*op_parse)->type = operator;
	(*op_parse)->fd_in = 0;
	(*op_parse)->fd_in_backup = 0;
	(*op_parse)->fd_out = 0;
	(*op_parse)->fd_out_backup = 0;
	(*op_parse)->flag = 0;
}

t_token	*pars_operator(t_token **token_list, t_expression **op_parse)
{
	int		operator;
	t_token	*to_free;

	to_free = *token_list;
	operator = check_for_operator((*token_list)->str);
	if (operator)
	{
		(*op_parse) = calloc(1, sizeof(t_expression));
		if (!*op_parse)
			exit(1);
		fill_val_opparse(op_parse, operator, *token_list);
		*token_list = (*token_list)->next;
		free(to_free->str);
		free(to_free);
	}
	return (*token_list);
}
