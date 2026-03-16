/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:24:44 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/17 13:38:57 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*timer(void *head)
{
	struct timeval	t_current;
	t_philosopher	*temp;
	long			timestamp;
	int				locked;

	temp = (t_philosopher *)head;
	pthread_mutex_lock(&temp->clock->stop_mutex);
	locked = 1;
	while (!temp->pt_to_stop->stop_simulation 
		&& temp->pt_to_stop->enough_counter != 0)
	{
		pthread_mutex_unlock(&temp->clock->stop_mutex);
		locked = 0;
		usleep(temp->time_to_die / 2 * 1000);
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
		check_for_death(temp, head, timestamp);
		temp = head;
		pthread_mutex_lock(&temp->clock->stop_mutex);
		locked = 1;
	}
	if (locked == 1)
		pthread_mutex_unlock(&temp->clock->stop_mutex);
	return (NULL);
}

void	*grab_fork(void *head)
{
	t_philosopher	*temp;
	int				unlock;

	unlock = 0;
	temp = (t_philosopher *)head;
	pthread_mutex_lock(&temp->clock->stop_mutex);
	while (!temp->pt_to_stop->stop_simulation)
	{
		unlock = 1;
		pthread_mutex_unlock(&temp->clock->stop_mutex);
		check_for_forks(temp);
		if (!check_enough(temp))
			return (NULL);
		sleeping(temp);
		thinking(temp);
		pthread_mutex_lock(&temp->clock->stop_mutex);
		unlock = 0;
	}
	if (unlock == 0)
		pthread_mutex_unlock(&temp->clock->stop_mutex);
	return (NULL);
}

void	create_threads(t_philosopher **socrates, pthread_t *time)
{
	t_philosopher	*temp;

	temp = *socrates;
	pthread_create(time, NULL, timer, temp);
	while (temp->next != *socrates)
	{
		pthread_create(&temp->thread, NULL, grab_fork, temp);
		temp = temp->next;
	}
	if (temp->next == *socrates)
		pthread_create(&temp->thread, NULL, grab_fork, temp);
}
