/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:22:05 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/26 16:14:40 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

exec_in_pipe(t_expression *node, t_env **env, t_variables **assignmentlist, char **r_envp)
{
    int     pid;
    pid = fork();
	if (pid == -1)
	{
		perror("fork unsuccesfull");
		exit(1);
	}
    else if (pid == 0)
    {
		dup2(node->fd_out, STDOUT_FILENO);
		node_eval(node->left, env, assignmentlist, r_envp);
    }
	exit(0);
}

int	exec_pipe(t_expression *node, t_env **env, t_variables **assignmentlist, char **r_envp)
{
	int     fd[2];
    pipe(fd);
	if (node->left)
	{
		node->left->fd_out = fd[1];
		exec_in_pipe(node->left, env, assignmentlist, r_envp);
	}
	if (node->right->Type == PIPE)
	{
		node = node->right;
		node->left->fd_in = fd[0];
		exec_pipe(node, env, assignmentlist, r_envp);
	}
	else 
	{
		node = node->right;
		node->fd_out;
		node_eval(node, env, assignmentlist, r_envp);
	}
	
}

