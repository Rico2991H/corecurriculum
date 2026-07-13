/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:23:57 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/25 12:08:05 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in(char *value)
{
	if (ft_strncmp("echo", value, 4) == 0 && ft_strlen(value) == 4)
		return (1);
	else if (ft_strncmp("cd", value, 2) == 0 && ft_strlen(value) == 2)
		return (1);
	else if (ft_strncmp("pwd", value, 3) == 0 && ft_strlen(value) == 3)
		return (1);
	else if (ft_strncmp("export", value, 6) == 0 && ft_strlen(value) == 6)
		return (1);
	else if (ft_strncmp("unset", value, 5) == 0 && ft_strlen(value) == 5)
		return (1);
	else if (ft_strncmp("env", value, 3) == 0 && ft_strlen(value) == 3)
		return (1);
	else if (ft_strncmp("exit", value, 4) == 0 && ft_strlen(value) == 4)
		return (1);
	return (0);
}

int	execute_builtin_logic(t_expression *cmdparse, 
		t_envs *b_envp, int e, t_variables **assign)
{
	int	status;

	status = 0;
	if (ft_strncmp("echo", cmdparse->value, 4) == 0)
		status = execute_echo(cmdparse, e);
	else if (ft_strncmp("cd", cmdparse->value, 2) == 0)
		status = execute_cd(cmdparse, &b_envp->env, assign);
	else if (ft_strncmp("pwd", cmdparse->value, 3) == 0)
		status = execute_pwd();
	else if (ft_strncmp("export", cmdparse->value, 6) == 0)
		status = execute_export(cmdparse, &b_envp->env, assign);
	else if (ft_strncmp("unset", cmdparse->value, 5) == 0)
		status = execute_unset(cmdparse, &b_envp->env, assign);
	else if (ft_strncmp("env", cmdparse->value, 3) == 0)
		status = execute_env(&b_envp->env);
	else if (ft_strncmp("exit", cmdparse->value, 4) == 0)
	{
		status = execute_exit(b_envp->g, cmdparse);
		exit(status);
	}
	fd_closer();
	return (status);
}

int	execute_built_in(t_expression *cmdparse, 
		t_envs *b_envp, int e, t_variables **assign)
{
	int		status;
	pid_t	pid;
	int		wstatus;

	status = 0;
	if (cmdparse->red)
	{
		pid = fork();
		if (pid == 0)
		{
			check_for_redirect(cmdparse);
			status = execute_builtin_logic(cmdparse, b_envp, e, assign);
			clean_heredoc(cmdparse);
			exit(status);
		}
		waitpid(pid, &wstatus, 0);
		status = convert_exit(wstatus);
		return (status);
	}
	status = execute_builtin_logic(cmdparse, b_envp, e, assign);
	clean_heredoc(cmdparse);
	return (status);
}
