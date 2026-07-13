/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:01:48 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/19 18:56:49 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static void	call_n_ass_fun(t_expression *node, 
		t_variables **assignmentlist, int e, t_envs *b_env)
{
	extract_assignments(node, assignmentlist, b_env);
	replace_exist_ass(node, *assignmentlist, b_env);
	expansion_checker(node, *assignmentlist, e);
	reset_fd(node);
}

int	node_eval(t_expression *node, t_envs *b_env, 
		t_variables **assignmentlist, int e)
{
	int	ret;

	ret = 0;
	if (!node)
		return (0);
	prep_heredoc(node);
	if (node->type == NODE_COMMAND)
	{
		if (built_in(node->value))
			ret = execute_built_in(node, b_env, e, assignmentlist);
		else
			ret = execution(node, b_env);
		return (ret);
	}
	if (node->type == NODE_ASSIGNMENT)
	{
		call_n_ass_fun(node, assignmentlist, e, b_env);
		return (0);
	}
	if (node->type == NODE_SUBSHELL)
		return (shell_subshell(node->child, b_env));
	return (0);
}

static int	node_is_or(int prev_status, t_variables **a_lst, 
			t_envs *b_env, t_expression *node)
{
	int	left_status;

	left_status = 0;
	if (prev_status == 0 || prev_status == START)
		left_status = priority(node->left, a_lst, b_env, prev_status);
	if (left_status != 0)
	{
		return (priority(node->right, a_lst, b_env, left_status));
	}
	else
	{
		while (node && node->right->type == NODE_OR)
			node = node->right; 
		if (node->right->type == NODE_COMMAND 
			|| node->right->type == NODE_ASSIGNMENT 
			|| node->right->type == NODE_SUBSHELL 
			|| node->right->type == NODE_PIPE)
			return (left_status);
		return (priority(node->right->right, a_lst, b_env, 0));
	}
	return (left_status);
}

int	priority(t_expression *node, t_variables **a_lst, 
	t_envs *b_env, int prev_status)
{
	int	left_status;

	left_status = 0;
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return (man_pipeline(node, b_env, prev_status));
	if (node->type == NODE_COMMAND || 
		node->type == NODE_ASSIGNMENT || node->type == NODE_SUBSHELL)
		return (node_eval(node, b_env, a_lst, prev_status));
	if (node->type == NODE_AND)
	{
		if (prev_status == 0 || prev_status == START)
			left_status = priority(node->left, a_lst, b_env, prev_status);
		if (left_status == 0 && (prev_status == 0 || prev_status == START))
		{
			return (priority(node->right, a_lst, b_env, left_status));
		}
		return (left_status);
	}
	if (node->type == NODE_OR)
		left_status = node_is_or(prev_status, a_lst, b_env, node);
	return (left_status);
}
