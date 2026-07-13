/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:52:28 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/25 13:27:10 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mark_quotes(char arg, int *in_double, 
	int *in_single)
{
	if (arg == '\'' && !*in_double)
	{
		*in_single = !*in_single;
		return (1);
	}
	if (arg == '"' && !*in_single)
	{
		*in_double = !*in_double;
		return (1);
	}
	return (0);
}

void	add_segment(t_token *token, char *str, int len, t_quote quote)
{
	t_segment	*tmp;
	t_segment	*seg;

	seg = malloc(sizeof(t_segment));
	if (!seg)
		exit (1);
	seg->str = ft_substr(str, 0, len);
	seg->quote = quote;
	seg->next = NULL;
	if (!token->segment)
		token->segment = seg;
	else
	{
		tmp = token->segment;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = seg;
	}
}

void	chang_i_j(int *j, int *i)
{
	(*j)++;
	*i = *j;
}

void	ass_q(int in_single, int in_double, t_quote *cur_q)
{
	if (in_single)
		*cur_q = Q_SINGLE;
	else if (in_double)
		*cur_q = Q_DOUBLE;
	else
		*cur_q = Q_NONE;
}

void	add_string(char *arg, int *j, t_token *tokens)
{
	t_qcheck	check;

	check.cur_q = Q_NONE;
	check.in_single = 0;
	check.in_double = 0;
	check.i = *j;
	while (arg[*j])
	{
		check.prev_single = check.in_single;
		check.prev_double = check.in_double;
		if (mark_quotes(arg[*j], &check.in_double, &check.in_single))
		{
			check_all(&check, tokens, j, arg);
			continue ;
		}
		if (!check.in_single && !check.in_double 
			&& (arg[*j] <= 32 || isspecial(arg[*j])))
			break ;
		(*j)++;
	}
	if (*j > check.i)
		add_segment(tokens, arg + check.i, *j - check.i, check.cur_q);
}
