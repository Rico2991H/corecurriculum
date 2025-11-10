/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatsleepraverepeat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:08:10 by rhoogend          #+#    #+#             */
/*   Updated: 2025/10/30 11:42:08 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eat(t_philosopher *head, t_sems *semaphores)
{
	struct timeval	t_current;
	struct timeval	t_eat;
	long			timestamp;

	gettimeofday(&t_current, NULL);
	timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
	sem_wait(semaphores->stop);
	sem_wait(semaphores->print);
	printf("%ld philosopher %d is eating\n", 
		timestamp, head->philosopher_nb);
	sem_post(semaphores->print);
	gettimeofday(&t_eat, NULL);
	head->last_eat = (t_eat.tv_sec * 1000L + t_eat.tv_usec / 1000l);
	usleep(head->time_to_eat * 1000);
	head->number_of_times--;
	sem_post(semaphores->stop);
	return (NULL);
}

void	sleeping(t_philosopher *head, t_sems *semaphores)
{
	struct timeval	t_current;
	long			timestamp;

	//sem_wait(semaphores->stop);
	gettimeofday(&t_current, NULL);
	timestamp = (t_current.tv_sec * 1000l + t_current.tv_usec / 1000l);
	sem_wait(semaphores->print);
	printf("%ld philosopher %d is sleeping\n", 
		timestamp, head->philosopher_nb);
	sem_post(semaphores->print);
	usleep(head->time_to_sleep * 1000);
	//sem_post(semaphores->stop);
}

void	thinking(t_philosopher *head, t_sems *semaphores)
{
	struct timeval	t_current;
	long			timestamp;

	gettimeofday(&t_current, NULL);
	timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
	sem_wait(semaphores->print);
	printf("%ld philosopher %d is thinking\n", 
		timestamp, head->philosopher_nb);
	sem_post(semaphores->print);
}

void	dying(long timestamp, t_philosopher *head, t_sems *semaphores)
{
	struct timeval	t_current;

	sem_wait(semaphores->stop);
	if (timestamp - head->last_eat > head->time_to_die 
		&& head->number_of_times != 0)
	{
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
		sem_wait(semaphores->print);
		printf("%ld philosopher %d died\n", timestamp, head->philosopher_nb);
		sem_post(semaphores->print);
		exit(1);
	}
	else
		sem_post(semaphores->stop);
}
