/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:36:02 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/16 11:40:58 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_arg	*fill_arg_val(t_token *token_list)
{
	t_arg	*new_arg;

	new_arg = malloc(sizeof(t_arg));
	if (!new_arg)
		exit(1);
	new_arg->arg = NULL;
	new_arg->segment = token_list->segment;
	token_list->segment = NULL;
	if (!new_arg->segment)
	{
		free(new_arg);
		return (NULL);
	}
	new_arg->to_remove = 0;
	new_arg->next = NULL;
	new_arg->expand_question = 1;
	return (new_arg);
}

void	add_arg_node(t_arg **arg, t_token *token_list)
{
	t_arg	*tmp;
	t_arg	*new_arg;

	tmp = *arg;
	new_arg = fill_arg_val(token_list);
	if (*arg == NULL)
	{
		*arg = new_arg;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_arg;
}

t_token	*parse_arg(t_token *token_list, t_expression **cmd_parse)
{
	t_arg	*args;
	t_token	*to_free;

	args = NULL;
	while (token_list && token_list->token_type == STRING)
	{
		to_free = token_list;
		add_arg_node(&args, token_list);
		token_list = token_list->next;
		free(to_free);
	}
	(*cmd_parse)->args = args;
	return (token_list);
}
