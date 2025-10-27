/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:35:18 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/11 15:37:42 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philosopher(t_philosopher *socrates)
{
	t_philosopher	*current;
	t_philosopher	*next;

	next = NULL;
	current = socrates;
	while (next != socrates)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

t_philosopher	*create_philosopher(int nb, char **argv, int argc)
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
	if (argc == 6)
		new_philosopher->number_of_times = ft_atoi(argv[5]);
	else
	{
		new_philosopher->number_of_times = -1;
	}
	new_philosopher->next = NULL;
	return (new_philosopher);
}

int	add_philosopher(t_philosopher **socrates, int i, char **args, int argc)
{
	t_philosopher	*new;
	t_philosopher	*last_node;

	new = create_philosopher(i, args, argc);
	if (!new)
		return (0);
	if (*socrates == NULL)
	{
		*socrates = new;
		new->next = new;
		return (1);
	}
	last_node = *socrates;
	while (last_node->next != *socrates)
		last_node = last_node->next;
	last_node->next = new;
	new->next = *socrates;
	return (1);
}

int	gather_philosophers(t_philosopher **socrates, int nb, char **args, int argc)
{
	int	i;

	i = 1;
	while (i <= nb)
	{
		if (!add_philosopher(socrates, i, args, argc))
		{
			free_philosopher(*socrates);
			*socrates = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}
