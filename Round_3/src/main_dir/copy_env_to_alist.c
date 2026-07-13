/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_to_alist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:13:54 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/20 08:39:52 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_variables	*alist_last(t_variables *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

static void	append_env_for_alist(t_variables **result, t_variables *new)
{
	t_variables	*last;

	if (result == NULL)
	{
		return ;
	}
	if (*result == NULL)
	{
		*result = new;
		return ;
	}
	last = alist_last(*result);
	last->next = new; 
}

static t_variables	*init_a_list(t_env *env)
{
	t_variables	*tmp;

	tmp = malloc(sizeof(t_variables));
	if (!tmp)
		return (NULL);
	tmp->name = ft_strdup(env->before_equal);
	tmp->value = ft_strdup(env->after_equal);
	tmp->next = NULL;
	return (tmp);
}

t_variables	*copy_env_to_alist(t_env *env)
{
	t_variables	*result;
	t_variables	*tmp;
	t_env		*temp;
	int			i;

	i = 0;
	temp = env;
	result = NULL;
	while (temp)
	{
		tmp = init_a_list(temp);
		append_env_for_alist(&result, tmp);
		temp = temp->next;
	}
	return (result);
}
