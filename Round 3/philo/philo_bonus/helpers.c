/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:07:27 by rhoogend          #+#    #+#             */
/*   Updated: 2025/10/30 10:11:08 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

t_philosopher	*create_philosopher(int nb, char **argv, 
			int argc, t_sems *semaphores)
{
	t_philosopher	*new_philosopher;

	new_philosopher = malloc(sizeof(t_philosopher));
	if (!new_philosopher)
		return (NULL);
	new_philosopher->last_eat = 0;
	new_philosopher->philosopher_nb = nb;
	new_philosopher->time_to_die = (long)ft_atoi(argv[2]);
	new_philosopher->time_to_eat = ft_atoi(argv[3]);
	new_philosopher->time_to_sleep = ft_atoi(argv[4]);
	new_philosopher->pt_to_sem = semaphores;
	if (argc == 6)
		new_philosopher->number_of_times = ft_atoi(argv[5]);
	else
		new_philosopher->number_of_times = -1;
	new_philosopher->next = NULL;
	return (new_philosopher);
}
