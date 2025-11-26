/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:07:08 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/24 12:44:43 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	reset_fd(t_expression *parse_cmds)
{
	int read_term;
	int write_term;
	if (parse_cmds->red)
	{
		read_term = open("/dev/tty", O_RDONLY);
		write_term = open("/dev/tty", O_WRONLY);
		dup2(write_term, STDOUT_FILENO);
		dup2(read_term, STDIN_FILENO);
		if(parse_cmds->red->Type == HEREDOC)
			unlink(parse_cmds->red->path);
		close(read_term);
		close(write_term);
	}
}

void 	handle_red_left(t_redirection *redirection)
{
	int fd;
	
	fd = open(redirection->name, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror ("Minishell: open");
		return;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		perror ("Minishell: dup2");
	close(fd);
}

void	handle_red_right(t_redirection *redirection)
{
	printf("handeling right redirect\n");
	int fd;
	
	fd = open(redirection->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("opened file\n");
	if (fd < 0)
	{
		perror ("Minishell: open");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror ("Minishell: dup2");
	close(fd);
}

void	handle_red_app_right(t_redirection *redirection)
{
	printf("handeling right app redirect\n");
	int fd;
	
	fd = open(redirection->name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	printf("opened file\n");
	if (fd < 0)
	{
		perror ("Minishell: open");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror ("Minishell: dup2");
	close(fd);
}

void	handle_red_hd(t_redirection *redirection)
{
	printf("handling heredocredirection\n");
	int fd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	redirection->path = ft_strjoin(cwd, "/tmpXXXX");
	free(cwd);

	fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Minishell: open");
		return;
	}
	write(fd, redirection->hdinput, ft_strlen(redirection->hdinput));
	close(fd);
	fd = open(redirection->path, O_RDONLY);
	if (fd < 0)
	{
		perror ("Minishell: open");
		return;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		return;
	close(fd);
}

void	check_for_redirect(t_expression *parse_cmds)
{	
	if (parse_cmds->red)
	{
		t_redirection *redirection;

		redirection = parse_cmds->red;
		if (redirection->Type == LEFT)
			handle_red_left(redirection);
		if (redirection->Type == RIGHT)
			handle_red_right(redirection);
		if(redirection->Type == HEREDOC)
			handle_red_hd(redirection);
		if(redirection->Type == APP_RIGHT)
			handle_red_app_right(redirection);
	}
	return;
}


