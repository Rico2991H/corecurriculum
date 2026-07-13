/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefile2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:55:15 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/26 13:22:35 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_rl_null(t_garbage *g)
{
	if (g->a_lst)
		free_assignment(g->a_lst);
	if (g->b_env->env)
		free_env(g->b_env->env);
	if (g->b_env)
		free(g->b_env);
	if (g->node)
		free_tree(g->node);
	if (g)
		free(g);
	fd_closer();
	rl_clear_history();
}

void	free_tree(t_expression *node)
{
	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->child);
	free_tree(node->right);
	clean_heredoc(node);
	free_array(node->split_paths);
	free_red(node->red);
	if (node->segment)
		free_seg(node->segment);
	free_args(node->args);
	free_assignment(node->assignment);
	free(node->value);
	free(node);
}

void	free_tokens(t_token *token_list)
{
	t_token	*temp;

	while (token_list)
	{
		temp = token_list;
		if (temp->segment)
		{
			free_seg(temp->segment);
			temp->segment = NULL;
		}
		token_list = token_list->next;
		if (temp->str)
			free(temp->str);
		temp->str = NULL;
		free(temp);
		temp = NULL;
	}
}

void	free_iter(t_garbage *g, char *path)
{
	(void)*path;
	g->t_n = NULL;
	free_tree(g->node);
	g->node = NULL;
}

void	free_files(t_files *files)
{
	t_files	*to_delete;

	to_delete = files;
	while (files)
	{
		files = files->next;
		free(to_delete->filename);
		free(to_delete);
		to_delete = files;
	}
}
