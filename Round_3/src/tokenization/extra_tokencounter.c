/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tokencounter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:50:29 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/16 12:49:00 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	c_pipes_and_or(char *arg, int *i, int *j, t_etoken *is_op)
{
	int	counter;

	counter = 0;
	(*i)++;
	if (*is_op == OPERATORS)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	while (arg[*j] == 124)
	{
		(*j)++;
		counter++;
		if (counter > 2)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (0);
		}
	}
	*is_op = OPERATORS;
	return (1);
}

int	c_andoperators(char *arg, int *i, int *j, t_etoken *is_op)
{
	int	counter;

	counter = 0;
	(*i)++;
	if (*is_op == OPERATORS)
	{
		ft_putstr_fd("syntax error near unexpected token `&'\n", 2);
		return (0);
	}
	while (arg[*j] == 38)
	{
		(*j)++;
		counter++;
	}
	if (counter != 2)
	{
		ft_putstr_fd("syntax error near unexpected token `&'\n", 2);
		return (0);
	}
	*is_op = OPERATORS;
	return (1);
}

int	c_redir_l(char *arg, int *i, int *j)
{
	int	counter;

	counter = 0;
	(*i)++;
	while (arg[*j] == 60)
	{
		(*j)++;
		counter++;
		if (counter > 2 || arg[*j] == 62)
		{
			ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
			return (0);
		}
	}
	return (1);
}

int	c_redir_r(char *arg, int *i, int *j)
{
	int	counter;

	counter = 0;
	(*i)++;
	while (arg[*j] == 62)
	{
		(*j)++;
		counter++;
		if (counter > 2 || arg[*j] == 60)
		{
			ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
			return (0);
		}
	}
	return (1);
}

int	c_dollarsigns(char *arg, int *i, int *j)
{
	(*j)++;
	if (arg[*j] == 63)
	{
		(*i)++;
		return (0);
	}
	else
	{
		while (arg[*j] != 32)
			(*j)++;
		return (0);
	}
	return (1);
}
