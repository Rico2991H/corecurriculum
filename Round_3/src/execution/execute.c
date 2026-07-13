/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:35:22 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/16 18:40:55 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static int	execution_pipe(t_expression *cmdparse, t_envs *b_env)
{
	char	*path;
	char	**args;

	path = path_finder(cmdparse);
	args = copy_args(cmdparse);
	path_ok(path, args, b_env);
	child_process(path, args, b_env);
	exit(1);
}

static int	execute_built_in_pipe(t_expression *cmdparse, 
		t_envs *b_env, int e)
{
	int	status;

	status = 0;
	if (ft_strncmp("echo", cmdparse->value, 4) == 0)
		status = execute_echo(cmdparse, e);
	else if (ft_strncmp("pwd", cmdparse->value, 3) == 0)
		status = execute_pwd();
	else if (ft_strncmp("export", cmdparse->value, 6) == 0)
		status = execute_export(cmdparse, &b_env->env, &cmdparse->assignment);
	else if (ft_strncmp("unset", cmdparse->value, 5) == 0)
		status = execute_unset(cmdparse, &b_env->env, &cmdparse->assignment);
	else if (ft_strncmp("env", cmdparse->value, 3) == 0)
		status = execute_env(&b_env->env);
	reset_fd(cmdparse);
	return (status);
}

void	exec_pipe_cmd(t_expression *node, t_envs *b_env, int e)
{
	int	status;

	status = 0;
	if (node->type == NODE_COMMAND)
	{
		if (built_in(node->value))
		{
			status = execute_built_in_pipe(node, b_env, e);
			free_env(b_env->env);
			free_iter(b_env->g, NULL);
			free_assignment(b_env->g->a_lst);
			free(b_env->g);
			free(b_env);
			exit (status);
		}
		else
			execution_pipe(node, b_env);
	}
}

char	**copy_no_args(t_expression *cmd_parse)
{
	char	**execve_args;

	execve_args = malloc(sizeof(char *) * 2);
	if (!execve_args)
		return (NULL);
	execve_args[0] = ft_strdup(cmd_parse->value);
	execve_args[1] = NULL;
	return (execve_args);
}
