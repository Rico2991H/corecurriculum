/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:47:45 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/13 14:18:29 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

void	file_thingy(t_expression *node)
{
	if (node->fd_in != STDIN_FILENO)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
	fd_closer();
	check_for_redirect(node);
	if (node->red && node->red->name == NULL)
	{
		free_tree(node);
		exit(1);
	}
}

void	file_thingy2(t_expression *node, t_p *p)
{
	if (node->fd_in != STDIN_FILENO)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
	}
	fd_closer();
	check_for_redirect(node);
	if (node->red && node->red->name == NULL)
	{
		free_tree(node);
		exit(1);
	}
	free(p);
}
