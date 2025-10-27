/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:14:43 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/13 13:04:01 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_free_and_exit(t_proces *proces)
{
	free_split_args(proces);
	free_split_paths(proces);
	exit(1); 
}

static void	close_helper(int *pfd, t_proces *proces)
{
	close(pfd[1]);
	close(pfd[0]);
	close(proces->fd);
}

/* creates a fork with a child procesfor the first cmd
this allows the parent proces in main
to stay active while running the first cmd*/
void	create_fork(int *pfd, t_proces *proces, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork unsuccesfull");
		exit(1);
	}
	else if (pid == 0)
	{
		if (dup2(proces->fd, STDIN_FILENO) < 0)
		{
			perror("dup2 failed");
			close_helper(pfd, proces);
			child_free_and_exit(proces);
		}
		if (dup2(pfd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2 failed");
			close_helper(pfd, proces);
			child_free_and_exit(proces);
		}
		close_helper(pfd, proces);
		exec_cmd(proces, envp);
	}
}

/* creates a fork with a child procesfor the 2nd cmd
this allows the parent proces in main
to stay active while running the 2nd cmd*/
void	create_fork_p2(int *pfd, t_proces *proces, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork unsuccesfull");
		exit(1);
	}
	else if (pid == 0)
	{
		if (dup2(proces->fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 failed");
			close_helper(pfd, proces);
			child_free_and_exit(proces);
		}
		if (dup2(pfd[0], STDIN_FILENO) < 0)
		{
			perror("dup2 failed");
			close_helper(pfd, proces);
			child_free_and_exit(proces);
		}
		close_helper(pfd, proces);
		exec_cmd(proces, envp);
	}
}
