/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:50:59 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/05 10:23:11 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static	t_variables	*a_lst_new(char *str)
{
	t_variables	*ret;

	ret = malloc(sizeof(t_variables));
	if (!ret)
		return (NULL);
	ret->name = get_before_equal(str);
	ret->value = get_after_equal(str);
	ret->next = NULL;
	return (ret);
}

int	export_env(t_expression *cmdparse, t_env **envp)
{
	t_env	*last;
	t_env	*new;

	if (!cmdparse->args)
		return (0);
	last = env_last(*envp);
	new = init_env(cmdparse->args->arg);
	if (!new)
	{
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		free_env(new);
		return (1);
	}
	if (valid_identifier(new->before_equal))
	{
		if (new->before_equal)
			ft_putstr_fd(new->before_equal, STDERR_FILENO);
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		free_env(new);
		return (1);
	}
	append_env_list(envp, new);
	return (0);
}

void	export_assign(t_expression *cmdparse, t_variables **assign)
{
	t_variables	*new;

	new = a_lst_new(cmdparse->args->arg);
	append_assign_lst(assign, new);
}

void	unset_env(t_expression *cmdparse, t_env **envp)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *envp;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(cmdparse->args->arg, 
				tmp->before_equal, ft_strlen(cmdparse->args->arg)) == 0 
			&& tmp->before_equal[ft_strlen(cmdparse->args->arg)] == '\0')
		{
			if (prev == NULL)
				*envp = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->after_equal);
			free(tmp->before_equal);
			tmp->after_equal = NULL;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	unset_assign(t_expression *cmdparse, t_variables **assign)
{
	t_variables	*tmp;
	t_variables	*prev;

	tmp = *assign;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(cmdparse->args->arg,
				tmp->name, ft_strlen(cmdparse->args->arg)) == 0 
			&& tmp->name[ft_strlen(cmdparse->args->arg)] == '\0')
		{
			if (prev == NULL)
				*assign = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			tmp->value = NULL;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
