/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:21:17 by rhoogend          #+#    #+#             */
/*   Updated: 2025/10/27 10:14:27 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include <string.h>

static void	freedom(t_proces *proces1, t_proces *proces2)
{
	free_split_args(proces1);
	free_split_args(proces2);
	free_split_paths(proces1);
	free_split_paths(proces2);
}

static void	init_processes(t_proces *proces1, t_proces *proces2, char **envp)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
	{
		perror("pipe failed");
		freedom(proces1, proces2);
		exit(1);
	}
	create_fork(pfd, proces1, envp);
	create_fork_p2(pfd, proces2, envp);
	close(pfd[0]);
	close(pfd[1]);
	close(proces1->fd);
	close(proces2->fd);
	wait(NULL);
	wait(NULL);
}

static void	prep_proces1(t_proces *proces1, char *arg, char *path)
{
	proces1->split_paths = ft_split(path, ':');
	if (!proces1->split_paths)
	{
		perror("split_paths failed");
		free(path);
	}
	proces1->split_args = ft_split(arg, ' ');
	if (!proces1->split_args)
	{
		perror("split_args failed");
		free(path);
		free_split_paths(proces1);
		exit(1);
	}
}

static void	prep_proces2(t_proces *proces1, 
			t_proces *proces2, char *arg, char *path)
{
	proces2->split_paths = ft_split(path, ':');
	if (!proces2->split_paths)
	{
		perror("split_paths failed");
		free(path);
		free_split_paths(proces1);
		free_split_args(proces1);
		exit(1);
	}
	proces2->split_args = ft_split(arg, ' ');
	if (!proces2->split_args)
	{
		perror("split_paths failed");
		free(path);
		free_split_paths(proces1);
		free_split_args(proces1);
		free_split_paths(proces2);
		exit(1);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_proces	proces1;
	t_proces	proces2;
	char		*path;

	if (argc != 5)
	{
		perror("function requires 4 args, <infile><cmd><cmd><outfile>");
		exit(1);
	}
	open_files(&proces1, &proces2, argv[1], argv[4]);
	path = getpath(envp);
	if (!path)
	{
		perror("getpath failed");
		exit(1);
	}
	prep_proces1(&proces1, argv[2], path);
	prep_proces2(&proces1, &proces2, argv[3], path);
	free(path);
	init_processes(&proces1, &proces2, envp);
	freedom(&proces1, &proces2);
}
