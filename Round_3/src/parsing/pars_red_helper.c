/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_red_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:48:29 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/16 10:40:59 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

int	extract_helper(t_token **curr)
{
	t_token	*redir;
	t_token	*next;
	t_token	*arg;

	while (*curr && (*curr)->token_type != PIPE 
		&& (*curr)->token_type != OPERATORS && (*curr)->token_type != PARENT)
	{
		if ((*curr)->token_type == REDIRECT)
		{
			redir = *curr;
			arg = redir->next;
			if (!arg)
				return (0);
			next = arg->next;
			*curr = next;
			free(redir->str);
			free(redir);
			free(arg);
		}
		else
			curr = &(*curr)->next;
	}
	return (1);
}
