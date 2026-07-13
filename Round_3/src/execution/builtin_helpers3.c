/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:27:43 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/25 10:24:11 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

void	print_export(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		printf("declare -x %s=%s\n", tmp->before_equal, tmp->after_equal);
		tmp = tmp->next;
	}
}

int	update_env(t_expression *cmdparse, t_env **envp)
{
	t_env	*tmp;
	char	*name;
	char	*value;
	int		len;
	int		len_name;

	name = get_before_equal(cmdparse->args->arg);
	value = get_after_equal(cmdparse->args->arg);
	len_name = ft_strlen(name);
	tmp = *envp;
	while (tmp)
	{
		len = ft_strlen(tmp->before_equal);
		if (!ft_strncmp(tmp->before_equal, name, len) && len == len_name)
		{
			free(name);
			free(tmp->after_equal);
			tmp->after_equal = value;
			return (0);
		}
		tmp = tmp->next;
	}
	free (name);
	free (value);
	return (1);
}

void	update_assign(t_expression *cmdparse, t_variables **assign)
{
	t_variables	*tmp;
	char		*name;
	char		*value;
	int			len;

	name = get_before_equal(cmdparse->args->arg);
	value = get_after_equal(cmdparse->args->arg);
	tmp = *assign;
	while (tmp)
	{
		len = ft_strlen(tmp->name);
		if (!ft_strncmp(tmp->name, name, len) && (size_t)len == ft_strlen(name))
		{
			free(name);
			free(tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
}
