/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:48:02 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/11 17:16:06 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cd(t_expression *cmdparse, t_env **envp, t_variables **assign)
{
	char	*oldpwd;
	int		ret;

	ret = 0;
	oldpwd = getcwd(NULL, 0);
	if (cmdparse->args && cmdparse->args->next != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (cmdparse->args)
		ret = change_dir(cmdparse->args->arg);
	else
		ret = get_homepwd(envp);
	cd_helper(envp, oldpwd, assign);
	return (ret);
}

static int	numeric_arg_check(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) || arg[i] == '-' || arg[i] == '+')
			i++;
		else
			return (1);
	}
	return (0);
}

static int	exit_status_checks(int i, t_expression *node, int ret)
{
	if (i == 2)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (numeric_arg_check(node->args->arg))
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	else
		ret = ft_atoi(node->args->arg);
	return (ret);
}

static int	set_exit_status(t_expression *node)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	if (!node->args)
		return (ret);
	while (node->args)
	{
		i++;
		ret = exit_status_checks(i, node, ret);
		node->args = node->args->next;
	}
	ret = ret % 256;
	if (ret < 0)
		ret = ret + 256;
	return (ret);
}

int	execute_exit(t_garbage *g, t_expression *node)
{
	int	exit_status;

	exit_status = set_exit_status(node);
	if (g)
	{
		free_rl_null(g);
		fd_closer();
		printf("exit\n");
	}
	return (exit_status);
}
