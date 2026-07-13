/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:41:43 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/09 16:01:51 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	path_cmd_check(char *slashed_cmd, char *path_cmd)
{
	if (!path_cmd)
	{
		perror("Error: command path");
		return (0);
	}
	if (access(path_cmd, F_OK) == 0)
	{
		free(slashed_cmd);
		return (1);
	}
	return (0);
}

char	*path_finder(t_expression *cmdparse)
{
	char	*slashed_cmd;
	char	*path_cmd;
	int		i;

	i = 0;
	if (cmdparse->value[0] == 0)
		return (NULL);
	path_cmd = path_slash_check(cmdparse);
	if (path_cmd)
		return (path_cmd);
	slashed_cmd = ft_strjoin("/", cmdparse->value);
	while (cmdparse->split_paths[i])
	{
		path_cmd = ft_strjoin(cmdparse->split_paths[i], slashed_cmd);
		if (path_cmd_check(slashed_cmd, path_cmd))
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	free(slashed_cmd);
	return (NULL);
}

static char	**new_execve(t_expression *cmd_parse)
{
	char	**execve_args;

	execve_args = malloc(sizeof(char *) * 2);
	if (!execve_args)
		return (NULL);
	execve_args[0] = ft_strdup(cmd_parse->value);
	execve_args[1] = NULL;
	return (execve_args);
}

static void	copy_args_helper(char **execve_args, t_arg *tmp, int i)
{
	while (tmp != NULL)
	{
		execve_args[i] = ft_strdup(tmp->arg);
		i++;
		tmp = tmp->next;
	}
	execve_args[i] = NULL;
}

char	**copy_args(t_expression *cmd_parse)
{
	char	**execve_args;
	t_arg	*tmp;
	int		i;

	i = 0;
	tmp = cmd_parse->args;
	if (!cmd_parse->args)
	{
		execve_args = new_execve(cmd_parse);
		return (execve_args);
	}
	i = t_arg_length(cmd_parse->args);
	tmp = cmd_parse->args;
	i++;
	execve_args = malloc(sizeof(char *) * (i + 1));
	if (!execve_args)
		return (NULL);
	i = 0;
	execve_args[i] = ft_strdup(cmd_parse->value);
	i++;
	copy_args_helper(execve_args, tmp, i);
	return (execve_args);
}
