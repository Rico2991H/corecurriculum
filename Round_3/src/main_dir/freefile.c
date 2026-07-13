/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freefile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:36:10 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/26 13:25:34 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_red(t_redirection *red)
{
	t_redirection	*tmp_red;

	while (red)
	{
		tmp_red = red;
		free(tmp_red->name);
		free(tmp_red->arrow);
		free(tmp_red->hdinput);
		free(tmp_red->path);
		if (tmp_red->segment)
		{
			free_seg(tmp_red->segment);
			tmp_red->segment = NULL;
		}
		red = red->next;
		free(tmp_red);
	}
}

void	free_args(t_arg *args)
{
	t_arg	*tmp_arg;

	while (args)
	{
		tmp_arg = args;
		free(tmp_arg->arg);
		if (tmp_arg->segment)
			free_seg(tmp_arg->segment);
		args = args->next;
		free(tmp_arg);
	}
}

void	free_assignment(t_variables *ass)
{
	t_variables	*tmp_ass;

	while (ass)
	{
		tmp_ass = ass;
		free(tmp_ass->name);
		free(tmp_ass->value);
		ass = ass->next;
		free(tmp_ass);
	}
	ass = NULL;
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_env(t_env *env)
{
	t_env	*tmp_env;

	tmp_env = NULL;
	while (env)
	{
		tmp_env = env->next;
		free(env->before_equal);
		free(env->after_equal); 
		free(env);
		env = tmp_env;
	}
}
