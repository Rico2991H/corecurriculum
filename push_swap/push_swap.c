/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:29:31 by rhoogend          #+#    #+#             */
/*   Updated: 2025/06/25 17:55:49 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <stdio.h>

static list_node	*create_node(int new_nbr, int new_pos)
{
	list_node	*new_node;
	
	new_node = malloc(sizeof(list_node));
	if (!new_node)
		return (NULL);
	new_node->nb = new_nbr;
	new_node->pos = new_pos;
	new_node->next = NULL;
	return (new_node);
}
	
void	prepend_node(list_node **head, int new_nbr, int new_pos)
{
	list_node *new; 
	
	new = create_node(new_nbr, new_pos);
	new->next = *head;
	*head = new;
}
/*
void	append_node(list_node **head, int new_nbr)
{
	list_node	*new;
	list_node	*last_node;
	new = create_node(new_nbr);
	last_node = *head;
	if (*head == NULL)
	{
		*head = new;
		return;
	}
	while(last_node->next)
		last_node = last_node->next;
	last_node->next = new;
}
*/
static int	chunkcount(int list_len)
{	
	if (list_len <= 20)
		return (2);
	if (list_len <= 100)
		return (4);
	if (list_len > 100 && list_len <= 300)
		return (6);
	if (list_len > 300 && list_len <= 500)
		return (11);
	return (-1);
}
#include <stdio.h>

void	push_swap(list_node **list)
{
	int 	listlen;
	int	numchunks;
	listlen = count_list(list);
	if(listlen <= 2 && (*list)->nb < (*list)->next->nb && listlen != 1)
		swap(*list);

	label_numbers(list);
	if(listlen == 3)
		sort3(list);
	if(listlen > 3)
	{
		numchunks = chunkcount(listlen);
		sort(list, numchunks, listlen);
	}
	else
		return;	
}

int	main(int argc,char **argv)
{
	list_node	*lista;
	int	nbr;
	int	i = 1;
	
	lista = NULL;
	if (argc <= 1 )
	{
		return (1);
	}
	while (i < argc)
	{
		nbr = atoi(argv[i]); // dont forget to change in ft
		i++;
		prepend_node(&lista, nbr, -1);
	}
	push_swap(&lista);
	return (0);
}


