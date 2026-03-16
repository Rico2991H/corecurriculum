/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 08:56:37 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/18 09:08:02 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_exec_path(t_proces *proces, char *slash_cmd, char **envp)
{
	int			i;
	char		*j_path;
	int			flag;

	i = -1;
	flag = 0;
	while (proces->split_paths[++i])
	{
		j_path = ft_strjoin(proces->split_paths[i], slash_cmd);
		if (!j_path)
		{
			perror("joining paths failed\n");
			return ;
		}
		if ((access(j_path, F_OK) == 0) && (access(j_path, X_OK) == 0))
		{
			flag = 1;
			if (execve(j_path, proces->split_args, envp) == -1)
				perror("execution fail\n");
		}
		free(j_path);
	}
	if (flag == 0)
		perror("path not found");
}
