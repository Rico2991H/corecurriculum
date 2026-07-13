/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 12:47:55 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/20 09:12:40 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static void	free_subshell(t_envs *orig_env)
{
	if (orig_env && orig_env->env)
		free_env(orig_env->env);
	if (orig_env && orig_env->g && orig_env->g->a_lst)
		free_assignment(orig_env->g->a_lst);
	if (orig_env && orig_env->g)
		free_iter(orig_env->g, NULL);
	if (orig_env && orig_env->g)
		free(orig_env->g);
	if (orig_env)
		free(orig_env);
	fd_closer();
}

int	shell_subshell(t_expression *node, t_envs *orig_env)
{
	t_garbage	*g2;
	pid_t		pid;
	int			status;
	int			i;

	status = 0;
	i = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed: ");
		return (127);
	}
	if (pid == 0)
	{
		g2 = orig_env->g;
		i = priority(node, &g2->a_lst, g2->b_env, START);
		free_subshell(orig_env);
		exit(i);
	}
	waitpid(pid, &status, 0);
	status = convert_exit(status);
	return (status);
}
