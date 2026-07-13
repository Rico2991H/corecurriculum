/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:55:34 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/25 12:05:59 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

void	write_newline(int flag)
{
	if (!flag)
		printf("\n");
}

static void	echo_str(t_arg *arg, int exit)
{
	int	i;

	(void)exit;
	i = 0;
	while (arg->arg[i])
	{
		printf ("%c", arg->arg[i]);
		i++;
	}
}

static int	echo_minus_n(t_arg *arg)
{
	int	i;

	i = 2;
	if (arg == NULL)
		return (0);
	if (ft_strncmp(arg->arg, "-n", 2) == 0)
	{
		while (arg->arg[i])
		{
			if (!(arg->arg[i] == 'e' || arg->arg[i] == 'n'))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	execute_echo(t_expression *cmdparse, int exit)
{
	t_arg		*tmp;
	int			flag;

	flag = 0;
	tmp = cmdparse->args;
	while (tmp)
	{
		if (flag == 0 && echo_minus_n(tmp))
		{
			flag = 1;
			tmp = tmp->next;
			if (tmp == NULL)
				return (0);
		}
		echo_str(tmp, exit);
		tmp = tmp->next;
		if (tmp && tmp->arg && tmp->arg[0] != 0)
			printf(" ");
	}
	write_newline(flag);
	return (0);
}
