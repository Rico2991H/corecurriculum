/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:13:54 by dmungunt          #+#    #+#             */
/*   Updated: 2025/11/15 15:01:25 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length_of_after_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		i++;
	}
	return (ft_strlen(str + i + 1));
}

int	length_of_before_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	return (i);
}

char	*get_after_equal(char *str)
{
	char	*result;

	result = ft_strchr(str, '=');
	if (!result)
		return(ft_strdup(""));
	return (ft_strdup(result + 1));
}

char	*get_before_equal(char *str)
{
	char	*result;
	int	i;
	int	j;

	j = 0;
	i = length_of_before_equal(str);
	result = malloc(sizeof(char) * i + 1);
	if(!result)
		return (NULL);
	while(j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[i] = '\0';
	return (result);
}

t_env	*env_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

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
	if(!tmp)
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
	int	i;

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