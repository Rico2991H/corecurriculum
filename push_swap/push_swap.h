/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:08:51 by rhoogend          #+#    #+#             */
/*   Updated: 2025/06/26 09:35:42 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node 
{
	int	nb;
	int	pos; 
	struct s_node *next;
}		list_node;

void	push_swap(list_node **list);
int	count_list(list_node **stacka);
int	list_scan_top(list_node **stacka, int list_len, int chunksize, int chunknb);
int	list_scan_bottom(list_node **stacka,int list_len, int chunksize, int chunknb);
void	label_numbers(list_node **stacka);
void	swap(list_node *stack);
void	push(list_node **stacka, list_node **stackb);
void	rotate(list_node **stack);
void	rev_rotate(list_node **stacka);
void	remove_node(list_node **head);
void	prepend_node(list_node **head, int new_nbr, int new_pos);
void	ss(list_node *stacka, list_node *stackb);
void	rr(list_node **stacka, list_node **stackb);
void	rrr(list_node **stacka, list_node **stackb);
void	sort3(list_node **list);
void	sort(list_node **list, int numchunks, int listlen);

#endif
