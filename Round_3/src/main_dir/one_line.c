/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:58:25 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/27 12:59:32 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static char	*getpath(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->before_equal, "PATH", 4) == 0)
			return (tmp->after_equal);
		tmp = tmp->next;
	}
	return (NULL);
}

void	one_line_less(char *input)
{
	free(input);
}

char	*one_line_less2(char **path, char *input, t_garbage *g, int *status)
{
	*status = 0;
	*path = getpath(g->b_env->env);
	input = readline("Minishell ");
	return (input);
}

void	one_line_less3(t_garbage *g, char *path)
{
	(void)*path;
	free_rl_null(g);
}
