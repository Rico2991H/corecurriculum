/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:22:05 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/19 15:59:45 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_p	*init_p(t_p *p)
{
	p = malloc(sizeof(t_p));
	p->count = 0;
	p->last_pid = -1;
	return (p);
}

int	man_pipeline(t_expression *node, t_envs *b_env, int exit)
{
	int	i;
	t_p	*p;
	int	status;
	int	last_status;

	i = 0;
	status = 0;
	last_status = 0;
	p = NULL;
	p = init_p(p);
	prep_all_heredoc(node);
	exec_pipe(node, b_env, exit, p);
	while (i < p->count)
	{
		waitpid(p->pid[i], &status, 0);
		if (p->pid[i] == p->last_pid)
			last_status = convert_exit(status);
		i++;
	}
	clean_all_heredoc(node);
	free(p);
	return (last_status);
}

int	exec_in_pipe(t_expression *node, t_envs *b_env, int e, t_p *p)
{
	p->pid[p->count] = fork();
	p->last_pid = p->pid[p->count];
	if (p->pid[p->count] == -1)
	{
		perror("fork unsuccesfull");
		fd_closer();
		exit(1);
	}
	else if (p->pid[p->count] == 0)
	{
		file_thingy(node);
		free(p);
		exec_pipe_cmd(node, b_env, e);
		perror("exec failed");
		exit(127);
	}
	else
	{
		p->count++;
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
	}
	return (0);
}

int	exec_last_in_pipe(t_expression *node, t_envs *b_env, int e, t_p *p)
{
	node = node->right;
	p->pid[p->count] = fork();
	p->last_pid = p->pid[p->count];
	if (p->pid[p->count] == -1)
	{
		perror("fork unsuccesfull");
		fd_closer();
		exit(1);
	}
	else if (p->pid[p->count] == 0)
	{
		file_thingy2(node, p);
		exec_pipe_cmd(node, b_env, e);
		perror("exec failed");
		exit(127);
	}
	else
	{
		p->count++;
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
	}
	return (0);
}

int	exec_pipe(t_expression *node, t_envs *b_env, int exit, t_p *p)
{
	int		fd[2];

	pipe(fd);
	node->left->fd_out = fd[1];
	if (node->fd_in != STDIN_FILENO)
		node->left->fd_in = node->fd_in;
	exec_in_pipe(node->left, b_env, exit, p);
	close(fd[1]);
	node->right->fd_in = fd[0];
	if (node->right->type == NODE_PIPE)
		exec_pipe(node->right, b_env, exit, p);
	else
		exec_last_in_pipe(node, b_env, exit, p);
	close(fd[0]);
	return (0);
}
