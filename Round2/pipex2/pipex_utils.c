/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:26:35 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/18 09:11:20 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/* open_files opens the files needed for the pipex program
one is an infile the other an outile*/
void	open_files(t_proces *proces1, t_proces *proces2, char *arg1, char *arg2)
{
	proces1->fd = open(arg1, O_RDONLY); 
	if (proces1->fd < 0)
	{
		perror("open input file failed\n");
		exit(1);
	}
	proces2->fd = open(arg2, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	if (proces2->fd < 0)
	{
		perror("open output file failed\n");
		exit(1);
	}
}

/*this functions creates the path,
* finds the path, checks if its executable
if so it runs execve to replace curr proces with the cmd
*/
void	exec_cmd(t_proces *proces, char **envp)
{
	char	*slash_cmd;

	slash_cmd = ft_strjoin("/", proces->split_args[0]);
	find_exec_path(proces, slash_cmd, envp);
	child_free_and_exit(proces);
}

/* uses strncmp to allocate the right path in the envp array
if found it duplicates the path excluding the word path*/
char	*getpath(char **envp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (envp [i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_strdup(&envp[i][j + 5]));
}

void	free_split_args(t_proces *proces)
{
	int	i;

	i = 0;
	while (proces->split_args[i])
	{
		free(proces->split_args[i]);
		i++;
	}
	free(proces->split_args);
}

void	free_split_paths(t_proces *proces)
{
	int	i;

	i = 0;
	while (proces->split_paths[i])
	{
		free(proces->split_paths[i]);
		i++;
	}
	free(proces->split_paths);
}
