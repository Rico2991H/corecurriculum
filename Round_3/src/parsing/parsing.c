/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:07:06 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/26 13:13:50 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static t_expression	*parse_pipe(t_token **token_list, 
	t_expression *node, char *path, t_variables *assign)
{
	t_expression	*pipe;
	t_expression	*right;
	t_token			*to_free;

	to_free = *token_list;
	if (!(*token_list) || (*token_list)->token_type != PIPE)
		return (node);
	*token_list = (*token_list)->next;
	free(to_free->str);
	free(to_free);
	right = val_pars(token_list, path, assign, node->g);
	pipe = ft_calloc(1, sizeof(t_expression));
	if (!pipe)
		exit(1);
	pipe->left = node;
	pipe->right = right;
	pipe->type = NODE_PIPE;
	return (pipe);
}

t_expression	*val_pars(t_token **token_list, 
	char *path, t_variables *assignlist, t_garbage *g)
{
	t_expression	*cmdparse;
	t_variables		*assignment;

	assignment = NULL;
	cmdparse = ft_calloc(1, sizeof(t_expression));
	if (!cmdparse)
		exit(1);
	cmdparse->g = g;
	g->node = cmdparse;
	cmdparse->fd_in = 0;
	cmdparse->fd_out = 1;
	cmdparse->fd_in_backup = dup(STDIN_FILENO);
	cmdparse->fd_out_backup = dup(STDOUT_FILENO);
	(*token_list) = parse_expansion((*token_list)->segment, 
			token_list, assignlist);
	cmdparse->red = extr_pars_red(token_list, g);
	(*token_list) = parse_assign(*token_list, &assignment);
	(*token_list) = parse_command(*token_list, &cmdparse, &assignment, path);
	(*token_list) = parse_arg(*token_list, &cmdparse);
	(*token_list) = val_pars_recursion(&cmdparse, 
			*token_list, path, assignlist);
	if (*token_list && (*token_list)->token_type == PIPE)
		cmdparse = parse_pipe(token_list, cmdparse, path, assignlist);
	return (cmdparse);
}
