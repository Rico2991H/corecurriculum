/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:33 by dmungunt          #+#    #+#             */
/*   Updated: 2026/03/02 12:20:16 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (g_global_var == PROMPT || g_global_var == 130)
	{
		g_global_var = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_exec_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	sig_hd_handler(int sig)
{
	(void)sig;
	fd_closer();
	exit(130);
}

void	set_exit(t_garbage **g)
{
	if (g_global_var == 130)
		(*g)->b_env->exit = 130;
}

void	signal_set(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
