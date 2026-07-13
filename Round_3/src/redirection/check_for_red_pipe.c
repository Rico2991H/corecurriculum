/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_red_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:05:06 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/03 11:22:15 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_red_right_pipe(t_redirection *redirection, 
	t_expression *parse_cmds)
{
	int	fd;

	fd = open(redirection->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror ("Minishell: open");
		return ;
	}
	close(parse_cmds->fd_out);
	parse_cmds->fd_out = fd;
}

int	check_for_red_pipe(t_expression *parse_cmds)
{
	t_redirection	*redirection;

	if (parse_cmds->red)
	{
		redirection = parse_cmds->red;
		while (redirection)
		{
			if (redirection->type == RIGHT)
				handle_red_right_pipe(redirection, parse_cmds);
			redirection = redirection->next;
		}
		return (1);
	}
	return (0);
}
