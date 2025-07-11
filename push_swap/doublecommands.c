/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublecommands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:05:58 by rhoogend          #+#    #+#             */
/*   Updated: 2025/07/02 14:54:15 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	ss(list_node *stacka, list_node *stackb)
{
	swap(stacka);
	swap(stackb);
}

void	rr(list_node **stacka, list_node **stackb)
{
	rotate(stacka);
	rotate(stackb);
}

void	rrr(list_node **stacka, list_node **stackb)
{
	rev_rotate(stacka);
	rev_rotate(stackb);
}
