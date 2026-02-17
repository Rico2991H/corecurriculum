/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:11:13 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/19 12:30:04 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/* 
this is a function about something fejfwf*/
int	check_enough(t_philosopher *temp)
{
	if (temp->number_of_times == 0)
	{
		printf("philosopher %d had enough\n", temp->philosopher_nb);
		return (0);
	}
	return (1);
}

void	*timer(void *head)
{
	struct timeval	t_current;
	t_philosopher	*temp;
	long			timestamp;

	temp = (t_philosopher *)head;
	while (1)
	{
		usleep(temp->time_to_die / 2 * 1000);
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
		dying(timestamp, temp, temp->pt_to_sem);
	}
	return (NULL);
}
