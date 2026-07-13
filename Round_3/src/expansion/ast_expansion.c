/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:15:50 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/16 16:58:45 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_ast(t_arg **arg, char *filename)
{
	t_arg	*new_arg;
	t_arg	*tmp;

	tmp = *arg;
	(*arg)->to_remove = 1;
	new_arg = malloc(sizeof(t_arg));
	new_arg->to_remove = 0;
	new_arg->arg = ft_strdup(filename);
	new_arg->next = NULL;
	new_arg->segment = NULL;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_arg;
}

static void	iter_arg(t_arg *arg_trav, t_files *files)
{
	int	i;

	i = 0;
	while (arg_trav->arg[i])
	{
		if (arg_trav->arg[i] == '*' && arg_trav->segment->quote == Q_NONE)
		{
			while (files)
			{
				if (check_files(arg_trav->arg, i, files))
					expand_ast(&arg_trav, files->filename);
				files = files->next;
			}
		}
		i++;
	}
}

void	check_for_ast(t_expression *cmd_parse)
{
	t_files	*files;
	t_arg	*arg_trav;

	files = retrieve_files();
	arg_trav = cmd_parse->args;
	while (arg_trav)
	{
		iter_arg(arg_trav, files);
		arg_trav = arg_trav->next;
	}
	free_files(files);
}

static void	free_temp_arg(t_arg *temp_arg)
{
	free(temp_arg->arg);
	free_seg(temp_arg->segment);
	free(temp_arg);
}

void	remove_ast(t_arg **arg_trav)
{
	t_arg	*curr; 
	t_arg	*prev;
	t_arg	*temp_arg;

	curr = *arg_trav;
	prev = NULL;
	temp_arg = NULL;
	while (curr)
	{
		if (curr->to_remove == 1)
		{
			temp_arg = curr;
			if (prev == NULL)
				*arg_trav = curr->next;
			else
				prev->next = curr->next;
			curr = curr->next;
			free_temp_arg(temp_arg);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
