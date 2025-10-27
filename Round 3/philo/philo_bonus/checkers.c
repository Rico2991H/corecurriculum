/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:11:13 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/19 15:35:18 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	check_for_death(t_philosopher *temp, 
	t_philosopher *head, long timestamp)
{
	while (temp->next != head)
	{
		dying(timestamp, temp);
		temp = temp->next;
	}
	if (temp->next == head)
		dying(timestamp, temp);
}

int	check_enough(t_philosopher *temp)
{
	if (temp->number_of_times == 0 && !temp->pt_to_stop->stop_simulation)
	{
		printf("philosopher %d had enough\n", temp->philosopher_nb);
		temp->pt_to_stop->enough_counter--;
		return (0);
	}
	return (1);
}
