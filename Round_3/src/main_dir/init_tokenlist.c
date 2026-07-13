/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokenlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:05:41 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/16 16:02:46 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*prepend_node(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->segment = NULL;
	new->token_type = 0;
	new->next = token;
	return (new);
}

t_token	*create_list(int i)
{
	int		j;
	t_token	*token;

	j = 0;
	token = NULL;
	while (j < i)
	{
		token = prepend_node(token);
		if (!token)
		{
			free(token);
			return (NULL);
		}
		j++;
	}
	return (token);
}
