/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_b_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:58:51 by dmungunt          #+#    #+#             */
/*   Updated: 2026/01/29 13:43:42 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

void	append_env(t_env **ret, t_env *new)
{
	t_env	*last;

	if (ret == NULL)
	{
		return ;
	}
	if (*ret == NULL)
	{
		*ret = new;
		return ;
	}
	last = env_last(*ret);
	last->next = new; 
}

t_env	*dup_env(t_env *lst)
{
	t_env	*ret;

	if (!lst)
		return (NULL);
	ret = malloc(sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->before_equal = ft_strdup(lst->before_equal);
	ret->after_equal = ft_strdup(lst->after_equal);
	ret->next = NULL;
	return (ret);
}

t_env	*dup_b_env(t_env *env)
{
	t_env	*tmp;
	t_env	*ret;
	t_env	*new;

	tmp = env;
	ret = NULL;
	while (tmp)
	{
		new = dup_env(tmp);
		append_env(&ret, new);
		tmp = tmp->next;
	}
	return (ret);
}

t_envs	*alloc_b_env(t_envs *b_env)
{
	t_envs	*copy_b_env;

	copy_b_env = malloc(sizeof(t_envs));
	if (!copy_b_env)
		return (NULL);
	copy_b_env->env = dup_b_env(b_env->env);
	copy_b_env->r_env = b_env->r_env;
	return (copy_b_env);
}
