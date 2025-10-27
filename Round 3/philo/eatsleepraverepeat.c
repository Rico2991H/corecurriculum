/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatsleepraverepeat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:08:10 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/17 13:22:53 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eat(t_philosopher *head)
{
	struct timeval	t_current;
	struct timeval	t_eat;
	long			timestamp;

	pthread_mutex_lock(&head->clock->stop_mutex);
	if (!head->pt_to_stop->stop_simulation)
	{
		pthread_mutex_unlock(&head->clock->stop_mutex);
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
		pthread_mutex_lock(&head->clock->print_mutex);
		printf("%ld philosopher %d is eating\n", 
			timestamp, head->philosopher_nb);
		pthread_mutex_unlock(&head->clock->print_mutex);
		gettimeofday(&t_eat, NULL);
		pthread_mutex_lock(&head->eat_mutex);
		head->last_eat = (t_eat.tv_sec * 1000L + t_eat.tv_usec / 1000l);
		usleep(head->time_to_eat * 1000);
		head->number_of_times--;
		pthread_mutex_unlock(&head->eat_mutex);
	}
	else
		pthread_mutex_unlock(&head->clock->stop_mutex);
	return (NULL);
}

void	sleeping(t_philosopher *head)
{
	struct timeval	t_current;
	long			timestamp;

	pthread_mutex_lock(&head->clock->stop_mutex);
	if (!head->pt_to_stop->stop_simulation)
	{
		pthread_mutex_unlock(&head->clock->stop_mutex);
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000l + t_current.tv_usec / 1000l);
		pthread_mutex_lock(&head->clock->print_mutex);
		printf("%ld philosopher %d is sleeping\n", 
			timestamp, head->philosopher_nb);
		pthread_mutex_unlock(&head->clock->print_mutex);
		usleep(head->time_to_sleep * 1000);
	}
	else
		pthread_mutex_unlock(&head->clock->stop_mutex);
}

void	thinking(t_philosopher *head)
{
	struct timeval	t_current;
	long			timestamp;

	pthread_mutex_lock(&head->clock->stop_mutex);
	if (!head->pt_to_stop->stop_simulation)
	{
		pthread_mutex_unlock(&head->clock->stop_mutex);
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
		pthread_mutex_lock(&head->clock->print_mutex);
		printf("%ld philosopher %d is thinking\n", 
			timestamp, head->philosopher_nb);
		pthread_mutex_unlock(&head->clock->print_mutex);
	}
	else
		pthread_mutex_unlock(&head->clock->stop_mutex);
}

void	dying(long timestamp, t_philosopher *head)
{
	struct timeval	t_current;

	pthread_mutex_lock(&head->clock->stop_mutex);
	pthread_mutex_lock(&head->eat_mutex);
	if (timestamp - head->last_eat > head->time_to_die && 
		!head->pt_to_stop->stop_simulation && head->number_of_times != 0)
	{
		pthread_mutex_unlock(&head->eat_mutex);
		head->pt_to_stop->stop_simulation = 1;
		pthread_mutex_unlock(&head->clock->stop_mutex);
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
		pthread_mutex_lock(&head->clock->print_mutex);
		printf("%ld philosopher %d died\n", timestamp, head->philosopher_nb);
		pthread_mutex_unlock(&head->clock->print_mutex);
	}
	else
	{
		pthread_mutex_unlock(&head->eat_mutex);
		pthread_mutex_unlock(&head->clock->stop_mutex);
	}
}
