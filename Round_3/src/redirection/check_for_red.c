/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:07:08 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/03 12:17:00 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_red_left(t_redirection *redirection)
{
	int	fd;

	fd = open(redirection->name, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror ("Minishell: open");
		exit (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror ("Minishell: dup2");
		close(fd);
		exit (1);
	}
	close(fd);
	return ;
}

static void	handle_red_right(t_redirection *redirection)
{
	int	fd;

	fd = open(redirection->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror ("Minishell: open");
		exit (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror ("Minishell: dup2");
		close (fd);
		exit (1);
	}
	close(fd);
}

static void	handle_red_app_right(t_redirection *redirection)
{
	int	fd;

	fd = open(redirection->name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		perror ("Minishell: open");
		exit (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror ("Minishell: dup2");
		close(fd);
		exit (1);
	}
	close(fd);
}

static void	handle_red_hd(t_redirection *redirection)
{
	int		fd;

	fd = open(redirection->path, O_RDONLY);
	if (fd < 0)
	{
		perror("Minishell: open");
		exit (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror ("Minishell: dup2");
		close(fd);
		exit (1);
	}
	close(fd);
}

int	check_for_redirect(t_expression *parse_cmds)
{
	t_redirection	*redirection;

	if (parse_cmds->red)
	{
		redirection = parse_cmds->red;
		while (redirection)
		{
			if (redirection->type == LEFT)
				handle_red_left(redirection);
			if (redirection->type == RIGHT)
				handle_red_right(redirection);
			if (redirection->type == HEREDOC)
				handle_red_hd(redirection);
			if (redirection->type == APP_RIGHT)
				handle_red_app_right(redirection);
			redirection = redirection->next;
		}
		return (1);
	}
	return (0);
}
