/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listcreation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:28:02 by rhoogend          #+#    #+#             */
/*   Updated: 2025/07/17 14:28:06 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <stdio.h>

static t_list_node	*create_node(int new_nbr, int new_pos)
{
	t_list_node	*new_node;

	new_node = malloc(sizeof(t_list_node));
	if (!new_node)
		return (NULL);
	new_node->nb = new_nbr;
	new_node->pos = new_pos;
	new_node->next = NULL;
	return (new_node);
}

void	remove_node(t_list_node **head)
{
	t_list_node	*node_to_remove;

	if (head == NULL || *head == NULL)
		return ;
	node_to_remove = *head;
	*head = (*head)->next;
	free (node_to_remove);
}

int	append_node(t_list_node **head, int new_nbr, int new_pos)
{
	t_list_node	*new;
	t_list_node	*last_node;

	new = create_node(new_nbr, new_pos);
	if (!new)
		return (0);
	last_node = *head;
	if (*head == NULL)
	{
		*head = new;
		return (1);
	}
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new;
	return (1);
}

int	prepend_node(t_list_node **head, int new_nbr, int new_pos)
{
	t_list_node	*new; 

	new = create_node(new_nbr, new_pos);
	if (!new)
		return (0);
	new->next = *head;
	*head = new;
	return (1);
}

void	free_list(t_list_node *list)
{
	t_list_node	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}
