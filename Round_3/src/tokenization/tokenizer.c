/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:28:58 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/25 13:25:13 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_all(t_qcheck *check, t_token *tokens, int *j, char *arg)
{
	if ((check->prev_single && !check->in_single) 
		|| (check->prev_double && !check->in_double))
	{
		if (*j == check->i)
			add_segment(tokens, "", 0, check->cur_q);
		else
			add_segment(tokens, arg + check->i, *j - check->i, check->cur_q);
	}
	else
	{
		if (*j > check->i)
			add_segment(tokens, arg + check->i, *j - check->i, check->cur_q);
	}
	chang_i_j(j, &check->i);
	ass_q(check->in_single, check->in_double, &check->cur_q);
}

void	add_group(char *arg, int *j, t_token *tokens, int *group)
{
	if (arg[*j] == 40)
	{
		tokens->str = ft_strdup("(");
		*group += 1;
	}
	if (arg[*j] == 41)
	{
		tokens->str = ft_strdup(")");
		*group -= 1;
	}
	tokens->token_type = PARENT;
	(*j)++;
}

int	token_helper(char *arg, int *j, t_token *tokens, int *group)
{
	if (arg[*j] == 124) 
	{
		add_pipes_and_or(arg, j, tokens);
		if (!arg[*j])
			return (1);
	}
	else if (arg[*j] == 38)
	{
		add_andoperators(arg, j, tokens);
		if (!arg[*j])
			return (1);
	}
	else if (arg[*j] == 40 || arg[*j] == 41)
		add_group(arg, j, tokens, group);
	else if (arg[*j] == 60) 
		add_redir_l(arg, j, tokens);
	else if (arg[*j] == 62)
		add_redir_r(arg, j, tokens);
	else if (arg[*j] > 32 && !isspecial(arg[*j]))
	{
		add_string(arg, j, tokens);
		tokens->token_type = STRING;
	}
	return (0);
}

int	tokenizer(char *arg, t_token *tokens)
{
	int		j;
	int		group;

	j = 0;
	group = 0;
	while (arg[j])
	{
		while (arg[j] == 32)
			j++;
		if (!arg[j])
			break ;
		if (token_helper(arg, &j, tokens, &group))
		{
			ft_putstr_fd("invalid command_line\n", 2);
			return (1);
		}
		tokens = tokens->next;
		if (if_group(group))
			return (group);
		if (!tokens)
			break ;
	}
	if (group > 0)
		ft_putstr_fd("syntax error near unexpected token `)'\n", 2);
	return (group);
}
