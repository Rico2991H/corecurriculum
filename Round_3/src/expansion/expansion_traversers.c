/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_traversers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:41:12 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/16 16:10:11 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parse_expansion(t_segment *seg, t_token **token_list, 
	t_variables *assignment)
{
	t_token	*tmp;

	tmp = *token_list;
	if (seg && seg->str[0] == '$' && dollar_sign_checks(seg->str) == 1)
	{
		seg_dup_helper(seg, &(*token_list)->str, assignment, 0);
		if (!(*token_list)->str[0] && (*token_list)->next)
		{
			(*token_list) = (*token_list)->next;
			free(tmp->str);
			free_seg(tmp->segment);
			free(tmp);
		}
		else
			free((*token_list)->str);
	}
	return (*token_list);
}
