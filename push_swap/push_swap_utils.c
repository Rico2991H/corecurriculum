/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:55:24 by rhoogend          #+#    #+#             */
/*   Updated: 2025/07/04 11:03:55 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "push_swap.h"

int	count_list(list_node **stacka)
{
	list_node	*traverser;
	int	counter;

	counter = 0;
	traverser = *stacka;
	while(traverser)
	{
		traverser = traverser->next;
		counter++;
	}
	return (counter);
}

void	label_numbers(list_node **stacka)
{
	list_node	*traverser1;
	list_node	*traverser2;
	int	i;
	
	i = 0;
	traverser1 = *stacka;
	traverser2 = (*stacka)->next;
	if (!traverser1 || !traverser2)
    		return;
	while (traverser1)
	{
		traverser1->pos = 0;
		traverser1 = traverser1->next;
	}	
	traverser1 = *stacka;
	while(traverser1)
	{
		while(traverser2)
		{
			if (traverser1->nb < traverser2->nb)
				traverser2->pos = traverser2->pos + 1;
			traverser2 = traverser2->next;
		}
		traverser1 = traverser1->next;
		traverser2 = *stacka;
	}
}

int	list_scan_top(list_node **stacka, int list_len,int chunksize, int chunknb)
{
	list_node	*traverser;
	int	pos_list;

	pos_list = 0;
	traverser = *stacka;
	while (pos_list <= list_len / 2 && traverser)
	{
		if (traverser->pos >= chunksize * chunknb - chunksize
		        && traverser->pos < chunksize * chunknb)
			       return (pos_list);
		traverser = traverser->next;
		pos_list++;
	}
	return (-1);
}
	
int	list_scan_bottom(list_node **stacka,int list_len, int chunksize, int chunknb)
{
	list_node	*traverser;
	int	pos_list;
	int	pin;

	pos_list = 0;
	pin = -1;
	traverser = *stacka;
	while (pos_list < list_len / 2 && traverser)
	{
			traverser = traverser->next;
			pos_list++;
	}
	while (pos_list != list_len && traverser)
	{
                if (traverser->pos >= chunksize * chunknb - chunksize
                        && traverser->pos < chunksize * chunknb)
				pin = pos_list;
		traverser = traverser->next;
		pos_list++;
	}
	return (pin);
}


