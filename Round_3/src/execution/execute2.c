/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:01:48 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/02 12:19:53 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

void	child_process(char *path, char **args, t_envs *b_env)
{
	char	**array;

	array = env_to_array(b_env->env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, args, array);
	perror(args[0]);
	free_array(array);
	free_pipe_stuff(path, args, b_env);
	exit(1);
}

int	convert_exit(int status)
{
	int	sig;

	sig = 0;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGPIPE)
			perror("Broken pipe");
		return (128 + sig);
	}
	return (1);
}

static void	child_execution(char *path, char **args, 
							t_expression *cmdparse, t_envs *b_env)
{
	if (!cmdparse->split_paths)
		path = NULL;
	else
		path = path_finder(cmdparse);
	args = copy_args(cmdparse);
	check_for_redirect(cmdparse);
	fd_closer();
	if (cmdparse->red && cmdparse->red->name == NULL)
	{
		free_pipe_stuff(path, args, b_env);
		exit(1);
	}
	path_ok(path, args, b_env);
	child_process(path, args, b_env);
}

static int	parent_execution(pid_t pid, char *path, t_expression *cmdparse)
{
	int		status;

	(void)*path;
	status = 0;
	signal(SIGINT, sig_exec_handler);
	waitpid(pid, &status, 0);
	fd_closer();
	signal_set();
	g_global_var = 0;
	clean_heredoc(cmdparse);
	status = convert_exit(status);
	return (status);
}

int	execution(t_expression *cmdparse, t_envs *b_env)
{
	char	*path;
	char	**args;
	int		status;
	pid_t	pid;

	status = 0;
	path = NULL;
	args = NULL;
	pid = fork();
	g_global_var = 1;
	if (pid == -1)
	{
		perror("fork unsuccesfull");
		fd_closer();
		return (-1);
	}
	if (pid == 0)
		child_execution(path, args, cmdparse, b_env);
	else if (pid > 0)
		status = parent_execution(pid, path, cmdparse);
	return (status);
}
