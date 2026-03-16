/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:53:19 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/11 16:37:21 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_list_node *lista)
{
	t_list_node	*temp;

	temp = lista;
	while (temp && temp->next)
	{
		if (temp->nb > temp->next->nb)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	stupid_extra_fun(t_list_node **listb, int rev_rotations)
{
	while (rev_rotations != 0)
	{
		rev_rotateb(listb);
		rev_rotations--;
	}
}

void	rotate_inplace(t_list_node **list, int listlen, 
		int chunksize, int chunknb)
{
	int	pos_bot;
	int	pos_top;

	pos_top = list_scan_top(list, listlen, chunksize, chunknb);
	pos_bot = list_scan_bottom(list, listlen, chunksize, chunknb);
	if (pos_bot == -1 || pos_top < listlen - pos_bot)
	{
		while (pos_top > 0)
		{
			rotate(list);
			pos_top--;
		}
	}
	else
	{
		while (pos_bot < listlen)
		{
			rev_rotate(list);
			pos_bot++;
		}
	}
}

int	rotate_highest(t_list_node **stacka, int listlen)
{
	t_list_node	*traverser;
	int			pos_list;
	int			counter;

	pos_list = 0;
	counter = 0;
	traverser = *stacka;
	while (traverser)
	{
		if (traverser->pos == (listlen - 1))
			return (counter);
		counter++;
		traverser = traverser->next;
	}
	return (counter);
}

void	rotate_lowest(t_list_node **stacka)
{
	t_list_node	*traverser;
	int			min;
	int			counter;
	int			pin;

	counter = 0;
	traverser = *stacka;
	min = traverser->pos;
	while (traverser)
	{
		if (traverser->pos < min)
		{
			min = traverser->pos;
			pin = counter;
		}
		traverser = traverser->next;
		counter++;
	}
	traverser = *stacka;
	if (pin < 3)
		while ((*stacka)->pos != min)
			rotate(stacka);
	else
		while ((*stacka)->pos != min)
			rev_rotate(stacka);
}
