/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:47:45 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/03 10:10:09 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_all_heredoc(t_expression *parse_cmds)
{
	if (parse_cmds)
	{
		clean_heredoc(parse_cmds);
		clean_all_heredoc(parse_cmds->left);
		clean_all_heredoc(parse_cmds->right);
	}
}

void	clean_heredoc(t_expression *parse_cmds)
{
	t_redirection	*red;

	red = parse_cmds->red;
	while (red)
	{
		if (red->type == HEREDOC && red->path)
		{
			unlink(red->path);
		}
		red = red->next;
	}
}

void	reset_fd(t_expression *parse_cmds)
{
	if (parse_cmds->red)
	{
		dup2(parse_cmds->fd_out_backup, STDOUT_FILENO);
		dup2(parse_cmds->fd_in_backup, STDIN_FILENO);
		close(parse_cmds->fd_in_backup);
		close(parse_cmds->fd_out_backup);
	}
}
