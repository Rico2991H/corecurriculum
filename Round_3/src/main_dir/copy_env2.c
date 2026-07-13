/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 11:06:40 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/02 17:41:50 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_env_list(t_env **result, t_env *new)
{
	t_env	*last;

	if (result == NULL)
	{
		return ;
	}
	if (*result == NULL)
	{
		*result = new;
		return ;
	}
	last = env_last(*result);
	last->next = new; 
}

t_env	*init_env(char *str)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return (NULL);
	tmp->before_equal = get_before_equal(str);
	tmp->after_equal = get_after_equal(str);
	tmp->next = NULL;
	return (tmp);
}

t_env	*copy_env(char **envp)
{
	t_env	*result;
	t_env	*tmp;
	int		i;

	i = 0;
	result = NULL;
	while (envp[i])
	{
		tmp = init_env(envp[i]);
		append_env_list(&result, tmp);
		i++;
	}
	return (result);
}
