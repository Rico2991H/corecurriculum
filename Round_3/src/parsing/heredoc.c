/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:39:05 by dmungunt          #+#    #+#             */
/*   Updated: 2026/03/02 11:54:56 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

void	hd_loop(t_hd_info *info, char *delimiter)
{
	while (1)
	{
		info->docarg = readline("heredoc> ");
		if (!info->docarg)
		{
			close(info->fd[1]);
			exit(130);
		}
		if (!ft_strncmp(info->docarg, delimiter, ft_strlen(delimiter))
			&& ft_strlen(info->docarg) == ft_strlen(delimiter))
		{
			free(info->docarg);
			break ;
		}
		write(info->fd[1], info->docarg, strlen(info->docarg));
		write(info->fd[1], "\n", 1);
		free(info->docarg);
	}
}

void	hd_child(char *delim, t_hd_info *info, 
		t_garbage *g, t_redirection **red)
{
	char	delimiter[1025];
	int		i;

	i = 0;
	while (delim[i])
	{
		delimiter[i] = delim[i];
		i++;
	}
	delimiter[i] = '\0';
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_hd_handler);
	free_hd_child(red, g);
	close(info->fd[0]);
	hd_loop(info, delimiter);
	fd_closer();
	close(info->fd[1]);
	exit(info->status);
}

void	hd_parent(t_hd_info *info)
{
	char	*new;

	close(info->fd[1]);
	info->input = ft_strdup("");
	while (info->n > 0)
	{
		info->n = read(info->fd[0], info->buf, sizeof(info->buf));
		info->buf[info->n] = '\0';
		info->tmp = info->input;
		new = ft_strjoin(info->input, info->buf);
		if (!new)
		{
			free(info->input);
			break ;
		}
		free(info->input);
		info->input = new;
	}
	close(info->fd[0]);
	if (WIFSIGNALED(info->status))
	{
		info->status = WTERMSIG(info->status);
		info->status = info->status + 128;
	}
}

void	init_info(t_hd_info *info)
{
	info->status = 0;
	info->docarg = NULL;
	info->input = NULL;
	info->n = 1;
	info->tmp = NULL;
}

char	*heredocinput(char *delimiter, t_garbage *g, t_redirection **red)
{
	t_hd_info	info;
	pid_t		pid;

	init_info(&info);
	if (pipe(info.fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		hd_child(delimiter, &info, g, red);
	}
	if (pid != 0)
	{
		waitpid(pid, &info.status, 0);
		hd_parent(&info);
		g_global_var = PROMPT;
		signal_set();
	}
	return (info.input);
}
