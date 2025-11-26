/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:29:23 by dmungunt          #+#    #+#             */
/*   Updated: 2025/11/26 12:12:17 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expression	*recursion(t_token **token_list, char *path)
{
	t_expression	*left;
	t_expression	*operator;
	t_token	*tmp_list;

	tmp_list = *token_list;
	operator = NULL;
	if (!tmp_list || ft_strncmp(")", tmp_list->str, 1) == 0)
	{
		if (ft_strncmp(")", tmp_list->str, 1) == 0)
		{
			printf("finds ')'\n");
		}
		return (NULL);
	}
	left = val_pars(&tmp_list, path);
	if (!tmp_list)
		return (left);
	if (tmp_list->token_type == OPERATORS || tmp_list->token_type == PIPE)
	{
		tmp_list = pars_operator(tmp_list, &operator);
		operator->left = left;
		operator->right = recursion(&tmp_list, path);
		printf("Recursion Ended\n");
	}
	*token_list = tmp_list;
	return (operator);
}

t_token	*val_pars_recursion(t_expression **cmdparse, t_token *token_list, char *path)
{
	t_token	*result;

	result = token_list;
	if (!token_list)
		return (NULL);
	if (result->token_type == PARENT && ft_strncmp("(", result->str, 1) == 0)
	{
		result = result->next;
		(*cmdparse)->Type = NODE_SUBSHELL;
		(*cmdparse)->child = recursion(&result, path);
		(*cmdparse)->right = NULL;
		(*cmdparse)->left = NULL;
		if (result->token_type == PARENT)
		{
			result = result->next;
		}
	}
	return (result);
}

t_expression	*recursion2(t_token **token_list, char *path)
{
	t_expression	*left;
	t_expression	*operator;
	t_token	*tmp_list;

	tmp_list = *token_list;
	operator = NULL;
	if (!tmp_list || ft_strncmp(")", tmp_list->str, 1) == 0)
	{
		if (ft_strncmp(")", tmp_list->str, 1) == 0)
		{
			printf("finds ')'\n");
		}
		return (NULL);
	}
	left = val_pars(&tmp_list, path);
	if (!tmp_list)
		return (left);
	if (tmp_list->token_type == OPERATORS)
	{
		tmp_list = pars_operator(tmp_list, &operator);
		operator->left = left;
		operator->right = recursion2(&tmp_list, path);
		printf("Recursion Ended\n");
	}
	*token_list = tmp_list;
	return (operator);
}