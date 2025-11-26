/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:32:42 by dmungunt          #+#    #+#             */
/*   Updated: 2025/11/17 16:11:36 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	find_command(char *command, t_expression **cmdparse)
{
	char	*slashed_cmd;
	char	*path_cmd;
	int		i;
	
	i = 0;
	if (built_in(command))
		return(1);
	slashed_cmd = ft_strjoin("/", command);
	while((*cmdparse)->split_paths[++i])
	{
		path_cmd = ft_strjoin((*cmdparse)->split_paths[i], slashed_cmd);
		if(!path_cmd)
		{
			//something error
			return(0);
		}
		if(access(path_cmd, F_OK) == 0)
			return(1);
	}
	return(0);
}

t_token	*parse_command(t_token *token_list, t_expression **cmdparse, t_variables **assignment, char *path)
{
	printf("in parse command\n");
	if(!token_list || token_list->token_type == OPERATORS)
	{
			printf("creating node_assignment\n");
			(*cmdparse)->Type = NODE_ASSIGNMENT;
			(*cmdparse)->assignment = *assignment;
			return(token_list);
	}	
	if(token_list->token_type && token_list->token_type == STRING)
	{
		printf("splittingpaths\n");
		(*cmdparse)->split_paths = ft_split(path, ':');
		if (!(*cmdparse)->split_paths)
		{
			perror("split_paths failed");
			free(path);
		}
		if (token_list->str && find_command(token_list->str, cmdparse))
		{
			(*cmdparse)->Type = NODE_COMMAND;
			(*cmdparse)->value = token_list->str;
			(*cmdparse)->assignment = *assignment;
			token_list = token_list->next;
		}
	}
	return(token_list);
}