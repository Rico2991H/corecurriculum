/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_assignments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:17:20 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/12 13:58:45 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	extractor(t_expression *cmd_parse, t_variables **assignment)
{
	t_variables *tmp;
	if (!cmd_parse->assignment)
		return;
	if (!*assignment)
	{
		*assignment = cmd_parse->assignment;
		return;	
	}
	tmp = *assignment;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = cmd_parse->assignment;
}

void    extract_assignments(t_expression *cmd_parse, t_variables **assignments)
{
	if(cmd_parse == NULL) // must set last node to NULL in earlier recursive function.
		return;
	if (cmd_parse->Type == NODE_ASSIGNMENT)
	{	
		printf("going into extractor\n");
		extractor(cmd_parse, assignments);
	}
	extract_assignments(cmd_parse->left, assignments);
	extract_assignments(cmd_parse->right, assignments);
}