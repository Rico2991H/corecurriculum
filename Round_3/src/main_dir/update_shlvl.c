/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:26:49 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/19 16:15:53 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

char	*get_env_value(t_env *env, char *keyword)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->before_equal, keyword, 5) == 0
			&& ft_strlen(tmp->before_equal) == 5)
		{
			return (tmp->after_equal);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_env(t_env *env, char *keyword, int lvl)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->before_equal, keyword, 5) == 0 
			&& ft_strlen(tmp->before_equal) == 5)
		{
			free(tmp->after_equal);
			tmp->after_equal = ft_itoa(lvl);
			return ;
		}
		tmp = tmp->next;
	}
}

void	update_shlvl(t_env **env)
{
	char	*value;
	int		level;

	value = get_env_value(*env, "SHLVL");
	if (!value)
	{
		set_env(*env, "SHLVL", 1);
		return ;
	}
	else
	{
		level = ft_atoi(value);
		if (level < 0)
			level = 0;
		else if (level >= 1000)
			level = 1;
		else
			level++;
	}
	set_env(*env, "SHLVL", level);
}
