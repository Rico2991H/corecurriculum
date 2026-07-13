/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:14:54 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/11 11:11:47 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_group(int group)
{
	if (group < 0)
	{
		ft_putstr_fd("syntax error near unexpected token `)'\n", 2);
		return (1);
	}
	return (0);
}

void	add_pipes_and_or(char *arg, int *j, t_token *tokens)
{
	int	len;
	int	i;

	i = *j;
	while (arg[*j] == 124)
		(*j)++;
	len = *j - i;
	tokens->str = ft_substr(&arg[i], 0, (*j - i));
	if (len == 1)
		tokens->token_type = PIPE;
	else
		tokens->token_type = OPERATORS;
}

void	add_andoperators(char *arg, int *j, t_token *tokens)
{
	int	i;

	i = *j;
	while (arg[*j] == 38)
	{
		(*j)++;
	}
	tokens->str = ft_substr(&arg[i], 0, (*j - i));
	tokens->token_type = OPERATORS;
}

void	add_redir_l(char *arg, int *j, t_token *tokens)
{
	int	i;

	i = *j;
	while (arg[*j] == 60)
	{
		(*j)++;
	}
	tokens->str = ft_substr(&arg[i], 0, (*j - i));
	tokens->token_type = REDIRECT;
}

void	add_redir_r(char *arg, int *j, t_token *tokens)
{
	int	i;

	i = *j;
	while (arg[*j] == 62)
		(*j)++;
	tokens->str = ft_substr(&arg[i], 0, (*j - i));
	tokens->token_type = REDIRECT;
}
