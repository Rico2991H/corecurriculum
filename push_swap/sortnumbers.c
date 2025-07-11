/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortnumbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:07:31 by rhoogend          #+#    #+#             */
/*   Updated: 2025/07/03 15:52:54 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <stdio.h>

int	scan_list(list_node **list)
{
	list_node	*temp;
	int	lowest;
	temp = *list;
	lowest = temp->pos;
	while(temp->next)
	{
		temp = temp->next;
		if (lowest > temp->pos)
			lowest = temp->pos;
	}

	return(lowest);
}
void	insert_top(list_node **lista, list_node **listb, int rotations)
{ 
	int	highest;

	highest = 0;
	while(rotations != 0)
	{
		rotate(listb);
		write(1,"rb\n",4);
		rotations--;
		highest++;
	}
	if (*lista)
	{
		push(lista, listb);
		write(1,"pb\n",4);
	}
	while(highest != 0)
	{
		rev_rotate(listb);
		write(1,"rrb\n",4);
		highest--;
	}
}
void	insert_bottom(list_node **lista, list_node **listb, int rotations, int listlen)
{
	//list_node	*temp;
	int	rev_rotations;
	int	highest;

	highest = 0;
	rev_rotations = listlen - rotations;
	while(rev_rotations != 0)
	{
		rev_rotate(listb);
		write(1,"rrb\n",4);
		rev_rotations--;
		highest++;
	}
	if (*lista)
	{
		push(lista, listb);
		write(1,"pb\n",4);
	}
	highest++;
	while(highest != 0)
	{
		rotate(listb);
		write(1,"rb\n",4);
		rev_rotations++;
		highest--;
	}
}

void	sortb(list_node **lista, list_node **listb )
{	
	list_node	*temp;
	int	listlen;
	int	lowest;
	int	rotations;

	rotations = 0;
	if (!*lista)
		return;
	if ((*listb)->next == NULL)
	{
		push(lista, listb);
		write(1,"pb\n",4);
		if ((*listb)->pos < (*listb)->next->pos)
		{
			swap(*listb);
			write(1,"sb\n",4);
		}
		return;
	}
	listlen = count_list(listb);
	lowest = scan_list(listb);
	temp = *listb;
	if ((*lista)->pos > (*listb)->pos)
	{
		push(lista,listb);
		write(1,"pb\n",4);
		return;		
	}
	if ((*lista)->pos < lowest)
	{
		push(lista,listb);
		write(1,"pb\n",4);
		rotate(listb);
		return;
	}
	while (temp && temp->next /*&& (*lista)->pos < temp->pos*/)
	{
		rotations++;
		if ((*lista)->pos > temp->next->pos /*&& (*lista)->pos < temp->pos*/)
			break;
		temp = temp->next;
	}
	if (!temp->next && (*lista)->pos < temp->pos)
		rotations++;
	if (rotations <= listlen / 2) 
	{
		insert_top(lista, listb, rotations);
		return;
	}
	else
	{
		insert_bottom(lista, listb, rotations, listlen);
		return;
	}
}

void	sort3(list_node **list)
{
	list_node	*pos1;
	list_node	*pos2;
	pos1 = *list;
	pos2 = (*list)->next;
	if (pos1->pos == 0 && pos2->nb != 1)
	{
		swap(*list);
		rotate(list);
	}
	if (pos1->pos == 1 && pos2->pos < pos2->next->pos)
                swap(*list);
	if (pos1->pos == 1 && pos2->pos > pos2->next->pos)
		rev_rotate(list);
	if (pos1->pos == 2 && pos2->pos < pos2->next->pos)
		rotate(list);
	if (pos1->pos == 2 && pos2->pos > pos2->next->pos)
	{
		swap(*list);
		rev_rotate(list);
	}
}

void	sort(list_node **list, int numchunks, int listlen)
{
	list_node	*listb;
	int	chunksize;
	int	chunknb;
	int	pos_bot;
	int	pos_top;
	int	counter;
	chunksize = (listlen + numchunks -1) / numchunks;
	chunknb = 1;
	listb = NULL;
	while (chunknb < 2 )//numchunks)
	{
		counter = chunksize;
		pos_top = list_scan_top(list, listlen,chunksize, chunknb);
		pos_bot = list_scan_bottom(list, listlen, chunksize, chunknb);
		while (counter != 0/*pos_top != -1 && pos_bot != -1*/) 
		{
			if (pos_bot == -1 || pos_top < listlen - pos_bot)
			{
				while(pos_top > 0)
				{			
					rotate(list);
					write(1,"ra\n",4);
					pos_top--;
				}
			}
			else
			{
				while(pos_bot < listlen )
				{			
					rev_rotate(list);
					write(1,"rra\n",5);
					pos_bot++;
				}
			}
			if (listb == NULL)
			{
				push(list, &listb);
				write(1,"pb\n",4);
			}
			sortb(list, &listb );
			listlen = count_list(list);
			pos_top = list_scan_top(list, listlen,chunksize, chunknb);
			pos_bot = list_scan_bottom(list, listlen, chunksize, chunknb);
			counter--;
			if (pos_top == -1 && pos_bot == -1)
				break;
		}
		chunknb++;
	}
	list_node	*traverser = listb;
	while(traverser)
	{
		printf("listb->pos %d\n", traverser->pos);
		printf("listb->nb %d\n", traverser->nb);
		traverser = traverser->next;
	}
	printf( "length of listb %d\n chunksize %d", listlen = count_list(&listb), chunksize);
}

