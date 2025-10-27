/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:11:13 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/17 13:41:24 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	grab_even(t_philosopher *temp, int *l_is_locked, int *r_is_locked)
{
	pthread_mutex_lock(&temp->clock->stop_mutex);
	if (!temp->pt_to_stop->stop_simulation)
	{
		pthread_mutex_unlock(&temp->clock->stop_mutex);
		pthread_mutex_lock(&temp->clock->print_mutex);
		printf("philosopher %d has taken a fork\n", temp->philosopher_nb);
		pthread_mutex_unlock(&temp->clock->print_mutex);
		pthread_mutex_lock(&temp->mutex);
		*l_is_locked = 1;
	}
	else
		pthread_mutex_unlock(&temp->clock->stop_mutex);
	pthread_mutex_lock(&temp->clock->stop_mutex);
	if (!temp->pt_to_stop->stop_simulation)
	{
		pthread_mutex_unlock(&temp->clock->stop_mutex);
		pthread_mutex_lock(&temp->clock->print_mutex);
		printf("philosopher %d has taken a fork\n", temp->philosopher_nb);
		pthread_mutex_unlock(&temp->clock->print_mutex);
		pthread_mutex_lock(&temp->next->mutex);
		*r_is_locked = 1;
	}
	else
		pthread_mutex_unlock(&temp->clock->stop_mutex);
}

void	grab_uneven(t_philosopher *temp, int *l_is_locked, int *r_is_locked)
{
	pthread_mutex_lock(&temp->clock->stop_mutex);
	if (!temp->pt_to_stop->stop_simulation)
	{
		pthread_mutex_unlock(&temp->clock->stop_mutex);
		pthread_mutex_lock(&temp->clock->print_mutex);
		printf("philosopher %d has taken a fork\n", temp->philosopher_nb);
		pthread_mutex_unlock(&temp->clock->print_mutex);
		pthread_mutex_lock(&temp->next->mutex);
		*r_is_locked = 1;
	}
	else
		pthread_mutex_unlock(&temp->clock->stop_mutex);
	pthread_mutex_lock(&temp->clock->stop_mutex);
	if (!temp->pt_to_stop->stop_simulation)
	{
		pthread_mutex_unlock(&temp->clock->stop_mutex);
		pthread_mutex_lock(&temp->clock->print_mutex);
		printf("philosopher %d has taken a fork\n", temp->philosopher_nb);
		pthread_mutex_unlock(&temp->clock->print_mutex);
		pthread_mutex_lock(&temp->mutex);
		*l_is_locked = 1;
	}
	else
		pthread_mutex_unlock(&temp->clock->stop_mutex);
}

void	check_for_forks(t_philosopher *temp)
{
	int		l_is_locked;
	int		r_is_locked;

	l_is_locked = 0;
	r_is_locked = 0;
	if (temp->philosopher_nb % 2 == 0)
		grab_even(temp, &l_is_locked, &r_is_locked);
	if (temp->philosopher_nb % 2 != 0)
		grab_uneven(temp, &l_is_locked, &r_is_locked);
	eat(temp);
	if (l_is_locked == 1)
	{
		pthread_mutex_unlock(&temp->mutex);
		l_is_locked = 0;
	}
	if (r_is_locked == 1)
	{
		pthread_mutex_unlock(&temp->next->mutex);
		r_is_locked = 0;
	}
}

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
	pthread_mutex_lock(&temp->clock->stop_mutex);
	if (temp->number_of_times == 0 && !temp->pt_to_stop->stop_simulation)
	{
		pthread_mutex_lock(&temp->clock->print_mutex);
		printf("philosopher %d had enough\n", temp->philosopher_nb);
		pthread_mutex_unlock(&temp->clock->print_mutex);
		temp->pt_to_stop->enough_counter--;
		pthread_mutex_unlock(&temp->clock->stop_mutex);
		return (0);
	}
	else
		pthread_mutex_unlock(&temp->clock->stop_mutex);
	return (1);
}
