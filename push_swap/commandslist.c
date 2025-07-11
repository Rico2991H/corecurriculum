/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandslist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:40:54 by rhoogend          #+#    #+#             */
/*   Updated: 2025/06/27 17:05:20 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <stdio.h>

void	remove_node(list_node **head)
{	
	if (head == NULL || *head == NULL)
		return;
		
	list_node	*node_to_remove;
	
	node_to_remove = *head;
	*head = (*head)->next;
	free(node_to_remove);
}

void	swap(list_node	*stack)
{
	if (!stack || !stack->next)
		return;

	int temp;
	int temppos;
	temp = stack->nb;
	temppos = stack->pos;
	stack->nb = stack->next->nb;
	stack->pos = stack->next->pos;
	stack->next->nb = temp;
	stack->next->pos = temppos;
}

void	push(list_node	**stacka, list_node	**stackb)
{
        if (!stacka || !*stacka || !stackb)
                return;
	prepend_node(stackb, (*stacka)->nb, (*stacka)->pos);
	remove_node(stacka);
}

void	rotate(list_node **stacka) 
{
	if (!*stacka || !(*stacka)->next)
		return;
		
	list_node	*temp; 
	list_node	*last;
	temp = *stacka; 
	last = *stacka; 
	 
	while(last->next) 
		last = last->next;
	*stacka = temp-> next;
	last->next = temp;
	temp->next = NULL;
} 

void	rev_rotate(list_node **stacka)	
{
	if (!*stacka || !(*stacka)->next)
		return;
		
	list_node	*new_last;
	list_node	*new_first;
	
	new_first = *stacka;
	new_last = *stacka;
	while(new_first->next)
		new_first = new_first->next;
	while(new_last->next != new_first)
		new_last = new_last->next;
	
	new_first->next = *stacka;
	new_last->next = NULL;
	*stacka = new_first;
}
