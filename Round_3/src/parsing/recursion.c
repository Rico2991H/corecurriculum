/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:29:23 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/26 12:58:18 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expression	*recursion(t_token **token_list, 
	char *path, t_variables *assign, t_garbage *g)
{
	t_expression	*left;
	t_expression	*operator;

	operator = NULL;
	if (!*token_list && !(*token_list)->segment->str)
	{
		printf("hello\n");
		return (NULL);
	}
	left = val_pars(token_list, path, assign, g);
	if (!*token_list)
		return (left);
	if ((*token_list)->token_type == PARENT 
		&& ft_strncmp(")", (*token_list)->str, 1) == 0)
		return (left);
	if ((*token_list)->token_type == OPERATORS 
		|| (*token_list)->token_type == PIPE)
	{
		*token_list = pars_operator(token_list, &operator);
		operator->left = left;
		operator->right = recursion(token_list, path, assign, g);
	}
	return (operator);
}

static t_token	*vpr_helper(t_token *result, t_token *to_free)
{
	if (result->token_type == PARENT 
		&& ft_strncmp(")", result->str, 1) == 0)
	{
		to_free = result;
		result = result->next;
		free(to_free->str);
		free(to_free);
	}
	return (result);
}

t_token	*val_pars_recursion(t_expression **cmdparse, 
	t_token *token_list, char *path, t_variables *assign)
{
	t_token	*result;
	t_token	*to_free;

	result = token_list;
	to_free = token_list;
	if (!token_list)
		return (NULL);
	if (result->token_type == PARENT && ft_strncmp("(", result->str, 1) == 0)
	{
		to_free = result;
		result = result->next;
		free(to_free->str);
		free(to_free);
		(*cmdparse)->type = NODE_SUBSHELL;
		(*cmdparse)->child = recursion(&result, path, assign, (*cmdparse)->g);
		(*cmdparse)->right = NULL;
		(*cmdparse)->left = NULL;
		result = vpr_helper(result, to_free);
	}
	return (result);
}
