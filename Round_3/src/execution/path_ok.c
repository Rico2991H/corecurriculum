/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_ok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:21:13 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/12 14:07:31 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipe_stuff(char *path, char **args, t_envs *b_env)
{
	if (path)
		free(path);
	free_iter(b_env->g, NULL);
	free_assignment(b_env->g->a_lst);
	free_env(b_env->env);
	free(b_env->g);
	free(b_env);
	free_array(args);
}

static	int	is_directory(char *path, char **arg)
{
	struct stat	st;

	if (ft_strncmp(arg[0], "./", 2) == 0 || ft_strncmp(arg[0], "/", 1) == 0)
	{
		if (stat(path, &st) == 0) 
		{
			return (S_ISDIR(st.st_mode));
		}
	}
	return (0);
}

static void	path_ok_helper(char *path, char **args, t_envs *b_env)
{
	if (access(path, F_OK))
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free_pipe_stuff(path, args, b_env);
		exit (127);
	}
	if (access(path, X_OK))
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		free_pipe_stuff(path, args, b_env);
		exit (126);
	}
}

void	path_ok(char *path, char **arg, t_envs *b_env)
{
	if (arg && arg[0][0] == 0)
	{
		free_pipe_stuff(path, arg, b_env);
		exit (0);
	}
	if (!path)
	{
		if (arg && arg[0])
			ft_putstr_fd(arg[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_pipe_stuff(path, arg, b_env);
		exit (127);
	}
	if (is_directory(path, arg))
	{
		if (arg && arg[0])
			ft_putstr_fd(arg[0], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		free_pipe_stuff(path, arg, b_env);
		exit(126);
	}
	path_ok_helper(path, arg, b_env);
}
