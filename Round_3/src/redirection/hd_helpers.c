/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:27:22 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/03 12:26:08 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

void	fill_fd_file(t_redirection *red)
{
	int		fd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	red->path = ft_strjoin(cwd, "/tmpXXXX");
	free(cwd);
	fd = open(red->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Minishell: open");
		exit(0);
	}
	write(fd, red->hdinput, ft_strlen(red->hdinput));
	close(fd);
}

void	prep_all_heredoc(t_expression *parse_cmds)
{
	if (parse_cmds)
	{
		prep_heredoc(parse_cmds);
		prep_all_heredoc(parse_cmds->left);
		prep_all_heredoc(parse_cmds->right);
	}
	return ;
}

int	prep_heredoc(t_expression *parse_cmds)
{
	t_redirection	*redirection;

	if (parse_cmds->red)
	{
		redirection = parse_cmds->red;
		while (redirection)
		{
			if (redirection->type == HEREDOC)
				fill_fd_file(redirection);
			redirection = redirection->next;
		}
		return (1);
	}
	return (0);
}
