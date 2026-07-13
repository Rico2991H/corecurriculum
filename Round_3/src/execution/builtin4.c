/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:23 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/13 14:13:08 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_helper(t_env **envp, char *oldpwd, t_variables **assign)
{
	char	*newpwd;

	(void)**assign;
	newpwd = getcwd(NULL, 0);
	update_env_var(envp, "OLDPWD", oldpwd, assign);
	update_env_var(envp, "PWD", newpwd, assign);
	free(oldpwd);
	free(newpwd);
}

int	get_homepwd(t_env **envp)
{
	char	*homepwd;
	int		ret;

	ret = 0;
	homepwd = find_user_name(envp);
	if (!homepwd)
		ret = change_dir("/home");
	else
	{
		ret = change_dir(homepwd);
		free(homepwd);
	}
	return (ret);
}

void	update_assign2(char *name, char *value, t_variables **assign)
{
	t_variables	*tmp;
	int			len;

	tmp = *assign;
	while (tmp)
	{
		len = ft_strlen(tmp->name);
		if (!ft_strncmp(tmp->name, name, len) && (size_t)len == ft_strlen(name))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}
