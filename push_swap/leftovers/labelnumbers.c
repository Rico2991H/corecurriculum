/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labelnumbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:55:24 by rhoogend          #+#    #+#             */
/*   Updated: 2025/07/02 18:01:01 by rhoogend         ###   ########.fr       */
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

	

	
