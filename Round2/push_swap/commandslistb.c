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

void	swapb(t_list_node	*stack)
{
	int	temp;
	int	temppos;

	if (!stack || !stack->next)
		return ;
	temp = stack->nb;
	temppos = stack->pos;
	stack->nb = stack->next->nb;
	stack->pos = stack->next->pos;
	stack->next->nb = temp;
	stack->next->pos = temppos;
	write (1, "sb\n", 3);
}

void	pushb(t_list_node	**stacka, t_list_node	**stackb)
{
	if (!stacka || !*stacka || !stackb)
		return ;
	if (!prepend_node(stackb, (*stacka)->nb, (*stacka)->pos))
		return ;
	remove_node(stacka);
	write (1, "pa\n", 3);
}

void	rotateb(t_list_node **stacka)
{
	t_list_node	*temp; 
	t_list_node	*last;

	if (!stacka || !*stacka || !(*stacka)->next)
		return ;
	temp = *stacka; 
	last = *stacka; 
	while (last->next) 
		last = last->next;
	*stacka = temp-> next;
	last->next = temp;
	temp->next = NULL;
	write(1, "rb\n", 3);
}

void	rev_rotateb(t_list_node **stacka)
{
	t_list_node	*new_last;
	t_list_node	*new_first;

	if (!stacka || !*stacka || !(*stacka)->next)
		return ;
	new_first = *stacka;
	new_last = *stacka;
	while (new_first->next)
		new_first = new_first->next;
	while (new_last->next != new_first)
		new_last = new_last->next;
	new_first->next = *stacka;
	new_last->next = NULL;
	*stacka = new_first;
	write(1, "rrb\n", 4);
}
