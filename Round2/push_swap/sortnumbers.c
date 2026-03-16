/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortnumbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:07:31 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/08 12:51:01 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

static void	push_back(t_list_node **listb, t_list_node **lista)
{
	int	listlen;
	int	rotations;
	int	rev_rotations;

	if (!listb || !*listb)
		return ;
	listlen = count_list(listb);
	while (listlen != 0)
	{
		rotations = rotate_highest(listb, listlen);
		rev_rotations = listlen - rotations;
		if (rotations < rev_rotations)
		{
			while (rotations != 0) 
			{
				rotateb(listb);
				rotations--;
			}
		}
		else
			stupid_extra_fun(listb, rev_rotations);
		pushb(listb, lista);
		listlen = count_list(listb);
	}
}

void	sort3(t_list_node **list)
{
	t_list_node	*pos1;
	t_list_node	*pos2;

	if (!list || !*list || !(*list)->next || !(*list)->next->next)
		return ;
	pos1 = *list;
	pos2 = (*list)->next;
	if (pos1->pos == 0 && pos2->nb != 2)
	{
		swap(*list);
		rotate(list);
	}
	else if (pos1->pos == 1 && pos2->pos == 0)
		swap(*list);
	else if (pos1->pos == 1 && pos2->pos == 2)
		rev_rotate(list);
	else if (pos1->pos == 2 && pos2->pos == 0)
		rotate(list);
	else if (pos1->pos == 2 && pos2->pos == 1)
	{
		swap(*list);
		rev_rotate(list);
	}
}

void	sort5(t_list_node **list)
{
	t_list_node	*listb;
	int			listlen;

	listb = NULL;
	listlen = count_list(list);
	if (listlen == 5)
	{
		rotate_lowest(list);
		push(list, &listb);
	}
	rotate_lowest(list);
	push(list, &listb);
	label_numbers(list);
	if (!is_sorted(*list))
		sort3(list);
	if (listlen == 5)
		pushb(&listb, list);
	pushb(&listb, list);
	label_numbers(list);
}

void	sort(t_list_node **list, int numchunks, int listlen, int chunksize)
{
	t_list_node	*listb;
	int			chunknb;
	int			counter;

	chunknb = 1;
	listb = NULL;
	while (chunknb <= numchunks)
	{
		counter = chunksize;
		while (counter != 0) 
		{
			rotate_inplace(list, listlen, chunksize, chunknb);
			push(list, &listb);
			if (listb->pos > chunksize * chunknb - (chunksize / 2))
				rotateb(&listb);
			listlen = count_list(list);
			counter--;
		}
		chunknb++;
	}
	push_back(&listb, list);
}
