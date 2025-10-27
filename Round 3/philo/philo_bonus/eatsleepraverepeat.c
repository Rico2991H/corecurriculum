/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatsleepraverepeat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:08:10 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/22 10:22:05 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eat(t_philosopher *head)
{
	struct timeval	t_current;
	struct timeval	t_eat;
	long			timestamp;
	gettimeofday(&t_current, NULL);
	timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
	printf("%ld philosopher %d is eating\n", 
	timestamp, head->philosopher_nb);
	if (!head->pt_to_stop->stop_simulation)
	{
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
		printf("%ld philosopher %d is eating\n", 
			timestamp, head->philosopher_nb);
		gettimeofday(&t_eat, NULL);
		head->last_eat = (t_eat.tv_sec * 1000L + t_eat.tv_usec / 1000l);
		usleep(head->time_to_eat * 1000);
		head->number_of_times--;
	}
	
	return (NULL);
}

void	sleeping(t_philosopher *head)
{
	struct timeval	t_current;
	long			timestamp;

	if (!head->pt_to_stop->stop_simulation)
	{
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000l + t_current.tv_usec / 1000l);
		printf("%ld philosopher %d is sleeping\n", 
			timestamp, head->philosopher_nb);
		usleep(head->time_to_sleep * 1000);
	}
}

void	thinking(t_philosopher *head)
{
	struct timeval	t_current;
	long			timestamp;

	if (!head->pt_to_stop->stop_simulation)
	{
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
		printf("%ld philosopher %d is thinking\n", 
			timestamp, head->philosopher_nb);
	}
}

void	dying(long timestamp, t_philosopher *head)
{
	struct timeval	t_current;

	if (timestamp - head->last_eat > head->time_to_die && 
		!head->pt_to_stop->stop_simulation && head->number_of_times != 0)
	{
		head->pt_to_stop->stop_simulation = 1;
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
		printf("%ld philosopher %d died\n", timestamp, head->philosopher_nb);
	}
}
