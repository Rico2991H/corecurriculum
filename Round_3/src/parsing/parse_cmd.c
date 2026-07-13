/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:32:42 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/13 14:06:12 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_command(char *command, t_expression *cmdparse)
{
	char	*slashed_cmd;
	char	*path_cmd;
	int		i;

	i = 0;
	if (built_in(command))
		return (1);
	slashed_cmd = ft_strjoin("/", command);
	while (cmdparse->split_paths[++i])
	{
		path_cmd = ft_strjoin(cmdparse->split_paths[i], slashed_cmd);
		if (!path_cmd)
			return (0);
		if (access(path_cmd, F_OK) == 0)
		{
			free(slashed_cmd);
			free(path_cmd);
			return (1);
		}
	}
	free(slashed_cmd);
	free(path_cmd);
	return (0);
}

static void	fill_val_cmd(t_expression **cmdparse, 
		t_token *token_list, t_variables **assignment, char *path)
{
	(*cmdparse)->split_paths = ft_split(path, ':');
	(*cmdparse)->type = NODE_COMMAND;
	(*cmdparse)->segment = token_list->segment;
	token_list->segment = NULL;
	(*cmdparse)->assignment = *assignment;
}

t_token	*parse_command(t_token *token_list, t_expression **cmdparse, 
	t_variables **assignment, char *path)
{
	t_token	*to_free;

	to_free = token_list;
	if (!token_list)
	{
		(*cmdparse)->type = NODE_ASSIGNMENT;
		(*cmdparse)->assignment = *assignment;
		return (NULL);
	}
	if (token_list && token_list->token_type == OPERATORS)
	{
		(*cmdparse)->type = NODE_ASSIGNMENT;
		(*cmdparse)->assignment = *assignment;
		return (token_list);
	}
	if (token_list && token_list->token_type 
		&& token_list->token_type == STRING)
	{
		fill_val_cmd(cmdparse, token_list, assignment, path);
		token_list = token_list->next;
		free(to_free);
	}
	return (token_list);
}
