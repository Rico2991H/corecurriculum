/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:34:41 by dmungunt          #+#    #+#             */
/*   Updated: 2025/11/05 13:35:34 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_equals(t_token *token)
{	
	if (!ft_strnstr(token->str, "=", ft_strlen(token->str)))
		return (0);
	return(1);
}

void	create_assign(t_token *token_list, t_variables **assignment)
{
	char	**key_val;
	
		t_variables *temp;
		t_variables *new_assignment;

		temp = *assignment;
		new_assignment = malloc(sizeof(t_variables));
		if (!new_assignment)
			return;
		key_val = ft_split(token_list->str, '=');
		new_assignment->name = key_val[0];
		new_assignment->value = key_val[1];
		new_assignment->next = NULL;
		free(key_val);
		if (*assignment == NULL)
			*assignment = new_assignment;
		else
		{
		while (temp->next)
			temp = temp->next;
		temp->next = new_assignment;
		}
}

t_token	*parse_assign(t_token *token_list, t_variables **assignment)
{
	while(token_list && token_list->token_type == STRING && find_equals(token_list))
	{
		create_assign(token_list, assignment);
		token_list = token_list->next;
	}
	return(token_list);
}