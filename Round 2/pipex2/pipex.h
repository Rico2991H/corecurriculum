/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:21:48 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/18 09:03:19 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_proces
{
	int		fd;
	char	*path;
	char	**split_paths;
	char	**split_args; 
	int		pid;
}	t_proces;

void	child_free_and_exit(t_proces *proces);
void	find_exec_path(t_proces *proces, char *slash_cmd, char **envp);
void	exec_cmd(t_proces *proces, char **envp);
char	*getpath(char **envp);
void	free_split_paths(t_proces *proces);
void	free_split_args(t_proces *proces);
void	create_fork(int *pfd, t_proces *proces, char **envp);
void	create_fork_p2(int *pfd, t_proces *proces, char **envp);
void	open_files(t_proces *proces1, 
			t_proces *proces2, char *arg1, char *arg2);
#endif