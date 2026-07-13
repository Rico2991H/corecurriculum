/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokencounter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:32:06 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/25 12:35:51 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	c_string(char *arg, int *i, int *j, t_etoken *is_op)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	(*i)++;
	while (arg[*j])
	{
		if ((!in_single && !in_double && arg[*j] <= 32) 
			|| (!in_single && !in_double && arg[*j] == ')')
			|| (!in_single && !in_double && isspecial(arg[*j])))
			break ;
		if (arg[*j] == '\'' && !in_double)
			in_single = !in_single;
		else if (arg[*j] == '"' && !in_single)
			in_double = !in_double;
		(*j)++;
	}
	if (in_single || in_double)
	{
		ft_putstr_fd("syntax error: unclosed quote\n", 2);
		return (0);
	}
	*is_op = STRING;
	return (1);
}

static int	c_group(char *arg, int *i, int *j, t_etoken *is_op)
{
	if ((*is_op == OPERATORS && arg[*j] == 40) 
		|| (*is_op != OPERATORS && arg[*j] == 41) || (*is_op == PARENT))
	{
		(*i)++;
		(*j)++;
	}
	else
	{
		ft_putstr_fd("syntax error near unexpected token `)'\n", 2);
		return (0);
	}
	*is_op = PARENT;
	return (1);
}

int	isspecial(char c)
{
	return (c == '>' || c == '<' 
		|| c == ')' || c == '(' || c == ')' || c == '&' 
		|| c == '|' );
}

static int	t_c_helper(char *arg, int *j, int *i, t_etoken *is_op)
{
	if (arg[*j] == 124)
		return (c_pipes_and_or(arg, i, j, is_op));
	else if (arg[*j] == 38)
		return (c_andoperators(arg, i, j, is_op));
	else if ((arg[*j] == 40 || arg[*j] == 41))
		return (c_group(arg, i, j, is_op));
	else if (arg[*j] == 60) 
		return (c_redir_l(arg, i, j));
	else if (arg[*j] == 62) 
		return (c_redir_r(arg, i, j));
	else if (arg[*j] > 32 && !isspecial(arg[*j]))
		return (c_string(arg, i, j, is_op));
	return (0);
}

int	token_counter(char *arg)
{
	int			i;
	int			j;
	t_etoken	prev_token;
	int			succes;

	prev_token = NOTHING;
	succes = 0;
	i = 0;
	j = 0;
	while (arg[j])
	{
		while (arg[j] == 32)
			j++;
		if (!arg[j])
			break ;
		succes = t_c_helper(arg, &j, &i, &prev_token);
		if (!succes)
			return (succes);
	}
	return (i);
}
