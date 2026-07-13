/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_red_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:47:56 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/16 16:58:31 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static void	expand_ast_red(t_redirection **red, char *filename)
{
	t_redirection	*new_red;
	t_redirection	*tmp;

	tmp = *red;
	new_red = malloc(sizeof(t_redirection));
	new_red->arrow = NULL;
	new_red->path = NULL;
	if (!new_red)
		return ;
	new_red->to_remove = 0;
	new_red->segment = NULL;
	new_red->name = ft_strdup(filename);
	new_red->hdinput = NULL;
	new_red->next = NULL;
	if ((*red)->arrow) 
		new_red->arrow = ft_strdup((*red)->arrow);
	if ((*red)->path)
		new_red->path = ft_strdup((*red)->path);
	new_red->type = (*red)->type;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_red;
	(*red)->to_remove = 1;
}

static void	iter_files_for_ast(t_files *files, t_redirection *tmp_red, int *i)
{
	while (files)
	{
		if (check_files(tmp_red->name, *i, files))
		{
			expand_ast_red(&tmp_red, files->filename);
		}
		files = files->next;
	}
}

void	check_for_ast_red(t_expression *cmd_parse)
{
	t_files			*files;
	t_files			*to_free;
	t_redirection	*tmp_red;
	int				i;

	files = retrieve_files();
	to_free = files;
	tmp_red = cmd_parse->red;
	i = 0;
	while (tmp_red)
	{
		while (tmp_red->name[i])
		{
			if (tmp_red->name[i] == '*' 
				&& tmp_red->segment->quote == Q_NONE)
				iter_files_for_ast(files, tmp_red, &i);
			i++;
			files = to_free;
		}
		i = 0;
		tmp_red = tmp_red->next;
	}
	free_files(to_free);
}

static void	free_temp_arg(t_redirection *temp_arg)
{
	free(temp_arg->arrow);
	free(temp_arg->name);
	free_seg(temp_arg->segment);
	free(temp_arg);
}

void	remove_ast_red(t_redirection **red_trav)
{
	t_redirection	*curr; 
	t_redirection	*prev;
	t_redirection	*temp_arg;

	curr = *red_trav;
	prev = NULL;
	temp_arg = NULL;
	while (curr)
	{
		if (curr->to_remove == 1)
		{
			temp_arg = curr;
			if (prev == NULL)
				*red_trav = curr->next;
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
