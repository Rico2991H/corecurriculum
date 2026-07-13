/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_red_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 13:14:11 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/03 10:10:33 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_red_type_l(t_expression *parse_cmds)
{
	t_redirection	*redirection;

	if (parse_cmds->red)
	{
		redirection = parse_cmds->red;
		while (redirection)
		{
			if (redirection->type == LEFT)
				return (1);
			if (redirection->type == HEREDOC)
				return (1);
			redirection = redirection->next;
		}
	}
	return (0);
}

int	check_red_type_r(t_expression *parse_cmds)
{
	t_redirection	*redirection;

	if (parse_cmds->red)
	{
		redirection = parse_cmds->red;
		while (redirection)
		{
			if (redirection->type == RIGHT)
				return (1);
			if (redirection->type == APP_RIGHT)
				return (1);
			redirection = redirection->next;
		}
	}
	return (0);
}
