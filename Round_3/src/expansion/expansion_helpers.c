/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:22:14 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/16 10:40:41 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*joinsegs(t_segment *seg)
{
	char	*joined_seg;
	char	*new_input;
	char	*buf;

	joined_seg = ft_strdup("");
	while (seg)
	{
		new_input = seg->str;
		buf = ft_strjoin(joined_seg, new_input);
		free(joined_seg);
		joined_seg = ft_strdup(buf);
		free(buf);
		seg = seg->next;
	}
	return (joined_seg);
}

void	seg_dup_helper(t_segment *seg, char **str, t_variables *ass, int e)
{
	t_segment	*tmp;

	tmp = seg;
	while (tmp)
	{
		tmp->str = clean_value(tmp->str, ass, tmp->quote, e); 
		tmp = tmp->next;
	}
	*str = joinsegs(seg);
}

void	quote_cleaner(t_expression *cmd_parse, t_variables *assignments, int e)
{
	t_arg			*arg_trav;
	t_redirection	*red;

	arg_trav = cmd_parse->args;
	red = cmd_parse->red;
	seg_dup_helper(cmd_parse->segment, &cmd_parse->value, assignments, e);
	while (red)
	{
		seg_dup_helper(red->segment, &red->name, assignments, e);
		if (red->type == HEREDOC)
			red->hdinput = clean_value(red->hdinput, 
					assignments, red->segment->quote, e);
		red = red->next;
	}
	while (arg_trav)
	{
		seg_dup_helper(arg_trav->segment, &arg_trav->arg, assignments, e);
		arg_trav = arg_trav->next;
	}
}

static void	add_ass_arg_node(t_arg **arg, char *arg_value)
{
	t_arg	*new_arg;
	t_arg	*tmp;

	tmp = *arg;
	new_arg = malloc(sizeof(t_arg));
	if (!new_arg)
		exit(1);
	new_arg->arg = ft_strdup(arg_value);
	new_arg->next = NULL;
	if (*arg == NULL)
	{
		*arg = new_arg;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_arg;
}

void	repl_cmds(t_expression *cmds_trav, t_variables *ass_trav)
{
	char	**buf;
	int		i;

	i = 1;
	buf = ft_split(ass_trav->value, ' ');
	free(cmds_trav->value);
	cmds_trav->value = ft_strdup(buf[0]);
	while (buf[i])
	{
		add_ass_arg_node(&cmds_trav->args, buf[i]);
		i++;
	}
	i = 0;
	while (buf[i])
	{
		free(buf[i]);
		i++;
	}
	free(buf);
}
