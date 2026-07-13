/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:27:05 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/20 12:09:26 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd :");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	execute_unset(t_expression *cmdparse, t_env **envp, t_variables **assign)
{
	if (!cmdparse->args)
		return (0);
	unset_env(cmdparse, envp);
	unset_assign(cmdparse, assign);
	return (0);
}

void	update_env_var(t_env **envp, char *keyword, 
			char *path, t_variables **assign)
{
	t_env	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->before_equal, keyword, ft_strlen(keyword)) == 0 
			&& tmp->before_equal[ft_strlen(keyword)] == '\0')
		{
			free(tmp->after_equal);
			tmp->after_equal = ft_strdup(path);
			update_assign2(keyword, tmp->after_equal, assign);
			return ;
		}
		tmp = tmp->next;
	}
}

int	change_dir(char *path)
{
	if (chdir(path))
	{
		perror("chdir :");
		return (1);
	}
	return (0);
}

char	*find_user_name(t_env **envp)
{
	t_env	*tmp;
	char	*str;

	tmp = *envp;
	while (tmp)
	{
		if (!ft_strncmp("USER", tmp->before_equal, 4) 
			&& ft_strlen(tmp->before_equal) == 4)
		{
			str = ft_strjoin("/home/", tmp->after_equal);
			return (str);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
