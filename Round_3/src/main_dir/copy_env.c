/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:13:54 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/06 12:04:54 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	length_of_after_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		i++;
	}
	return (ft_strlen(str + i + 1));
}*/

static int	length_of_before_equal(char *str)
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
	{
		return (ft_strdup(""));
	}
	return (ft_strdup(result + 1));
}

char	*get_before_equal(char *str)
{
	char	*result;
	int		i;
	int		j;

	j = 0;
	i = length_of_before_equal(str);
	if (i == 0)
		return (NULL);
	result = malloc(sizeof(char) * i + 1);
	if (!result)
		return (NULL);
	while (j < i)
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
