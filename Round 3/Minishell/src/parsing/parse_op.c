/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:33:29 by dmungunt          #+#    #+#             */
/*   Updated: 2025/11/05 13:34:19 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_token	*pars_operator(t_token *token_list, t_expression **op_parse)
{
	int	operator;

	//printf("enters and does check for operator\n");
	operator = check_for_operator(token_list->str);
	if (operator)
	{
		(*op_parse) = malloc(sizeof(t_expression));
		if (!*op_parse)
		{
			printf("malloc fail");
			exit(1);
		}
		(*op_parse)->value = token_list->str;
		(*op_parse)->Type = operator;
		(*op_parse)->right = NULL;
		token_list = token_list->next;
	}
	return (token_list);
}