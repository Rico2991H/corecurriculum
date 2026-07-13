/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:13:16 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/19 16:15:29 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

char	*path_slash_check(t_expression *node)
{
	if (ft_strncmp(node->value, "./", 2) == 0)
	{
		return (ft_strdup(node->value));
	}
	if (ft_strncmp(node->value, "/", 1) == 0)
	{
		return (ft_strdup(node->value));
	}
	return (NULL);
}

int	t_arg_length(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg)
	{
		i++;
		arg = arg->next;
	}
	return (i);
}

int	len_env(t_env *env)
{
	int		len;
	t_env	*tmp;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	char	*append_equal;
	t_env	*tmp;
	int		len;
	int		i;

	i = 0;
	tmp = env;
	len = len_env(env);
	array = malloc(sizeof(char *) * (len + 1));
	if (!array)
		exit (1);
	array[len] = NULL;
	while (i < len)
	{
		append_equal = ft_strjoin(tmp->before_equal, "=");
		array[i] = ft_strjoin(append_equal, tmp->after_equal);
		free(append_equal);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	return (array);
}
