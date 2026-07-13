/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_assignments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:17:20 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/06 15:19:37 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	update_env_a_lst(t_expression *cmdparse, t_env **env)
{
	t_env	*tmp;
	char	*name;
	char	*value;
	int		len;
	int		len_name;

	name = ft_strdup(cmdparse->assignment->name);
	value = ft_strdup(cmdparse->assignment->value);
	len_name = ft_strlen(name);
	tmp = *env;
	while (tmp)
	{
		len = ft_strlen(tmp->before_equal);
		if (!ft_strncmp(tmp->before_equal, name, len) && len == len_name)
		{
			free(name);
			free(tmp->after_equal);
			tmp->after_equal = value;
			return ;
		}
		tmp = tmp->next;
	}
	free(name);
	free(value);
}

void	replace_exist_ass(t_expression *node, 
		t_variables *assignmentlist, t_envs *b_env)
{
	t_variables	*tmp;

	if (!node->assignment)
		return ;
	if (!assignmentlist)
		return ;
	tmp = assignmentlist;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, node->assignment->name, 
				ft_strlen(node->assignment->name)))
		{
			free(tmp->value);
			tmp->value = ft_strdup(node->assignment->value);
			update_env_a_lst(node, &b_env->env);
		}
		tmp = tmp->next;
	}
}

void	extractor(t_expression *cmd_parse, t_variables **assignment)
{
	t_variables	*tmp;
	t_variables	*new;
	t_variables	*trav;

	trav = cmd_parse->assignment;
	while (trav)
	{
		new = malloc(sizeof(t_variables));
		if (!new)
			return ;
		new->name = ft_strdup(trav->name);
		new->value = ft_strdup(trav->value);
		new->next = NULL;
		if (!*assignment)
			*assignment = new;
		else
		{
			tmp = *assignment;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		trav = trav->next;
	}
}

void	extract_assignments(t_expression *cmd_parse, 
							t_variables **assignments, t_envs *b_env)
{
	if (cmd_parse == NULL)
		return ;
	if (cmd_parse->type == NODE_ASSIGNMENT)
	{
		if (!cmd_parse->assignment)
			return ;
		extractor(cmd_parse, assignments);
	}
	extract_assignments(cmd_parse->left, assignments, b_env);
	extract_assignments(cmd_parse->right, assignments, b_env);
}
