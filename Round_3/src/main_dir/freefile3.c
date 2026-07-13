/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefile3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:58:52 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/27 14:40:45 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_seg(t_segment *seg)
{
	t_segment	*to_free;

	while (seg)
	{
		to_free = seg;
		free(to_free->str);
		seg = seg->next;
		free(to_free);
	}
}

void	free_red2(t_redirection *red)
{
	t_redirection	*tmp_red;

	while (red)
	{
		tmp_red = red;
		free(tmp_red->name);
		free(tmp_red->arrow);
		free(tmp_red->hdinput);
		free(tmp_red->path);
		red = red->next;
		free(tmp_red);
	}
}

void	free_hd_child(t_redirection **red, t_garbage *g)
{
	free_env(g->b_env->env);
	free_assignment(g->a_lst);
	free(g->b_env);
	free_tokens(g->t_n);
	free_red2(*red);
	free(g->node);
	free(g);
}
