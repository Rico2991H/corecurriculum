/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:07:27 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/17 13:24:28 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* @brief Joins all the threads*/
void	join_threads(t_philosopher **socrates, pthread_t *time)
{
	t_philosopher	*temp;

	temp = *socrates;
	while (temp->next != *socrates)
	{
		pthread_join(temp->thread, NULL);
		temp = temp->next;
	}
	if (temp->next == *socrates)
		pthread_join(temp->thread, NULL);
	pthread_join(*time, NULL);
}

/* @brief Destroys Mutex for every philosopher*/
void	destroy_mutex(t_philosopher **socrates)
{
	t_philosopher	*temp;

	temp = *socrates;
	while (temp->next != *socrates)
	{
		pthread_mutex_destroy(&temp->mutex);
		pthread_mutex_destroy(&temp->eat_mutex);
		temp = temp->next;
	}
	if (temp->next == *socrates)
	{
		pthread_mutex_destroy(&temp->mutex);
		pthread_mutex_destroy(&temp->eat_mutex);
	}
	pthread_mutex_destroy(&temp->clock->stop_mutex);
	pthread_mutex_destroy(&temp->clock->print_mutex);
}

/*@brief initializes the Mutex for every philosopher.*/
void	init_mutex(t_philosopher **socrates, t_timer *clock)
{
	t_philosopher	*temp;

	temp = *socrates;
	while (temp->next != *socrates)
	{
		pthread_mutex_init(&temp->mutex, NULL);
		pthread_mutex_init(&temp->eat_mutex, NULL);
		temp = temp->next;
	}
	if (temp->next == *socrates)
	{
		pthread_mutex_init(&temp->mutex, NULL);
		pthread_mutex_init(&temp->eat_mutex, NULL);
	}
	pthread_mutex_init(&clock->stop_mutex, NULL);
	pthread_mutex_init(&clock->print_mutex, NULL);
}

static int	minus_checker(int *i, const char *nptr)
{
	int	sign;

	sign = 1;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
		{
			sign = -1;
			(*i)++;
			return (sign);
		}
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *nptr)
{
	long	number;
	int		i;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	sign = minus_checker(&i, nptr);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0') * sign;
		i++;
		if (number < -2147483648 || number > 2147483647)
		{
			write (1, "Error\n", 6);
			return (0);
		}
	}
	return ((int)number);
}
