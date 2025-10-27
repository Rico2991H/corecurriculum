/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:27:28 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/17 13:28:47 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*@Brief The main take 5 arguments 4 of which are obligatory. 
number_of_times_philosopher_must_eat is voluntary.
 @param number_of_philosophers
 @param time_to_die
 @param time_to_eat
 @param time_to_sleep
 @param number_of_times_philosopher_must_eat
 
 */
static void	init_sim(t_philosopher *head, t_simulation *sim)
{
	t_philosopher	*temp;

	temp = head;
	while (temp->next != head)
	{
		temp->pt_to_stop = sim;
		temp = temp->next;
	}
	if (temp->next == head)
		temp->pt_to_stop = sim;
}

static void	init_clock(t_philosopher *head, t_timer *clock)
{
	t_philosopher	*temp;

	temp = head;
	while (temp->next != head)
	{
		temp->clock = clock;
		temp = temp->next;
	}
	if (temp->next == head)
		temp->clock = clock;
}

static void	call_functions(t_philosopher *socrates, 
	t_timer *clock, t_simulation sim)
{
	init_sim(socrates, &sim);
	init_clock(socrates, clock);
	init_mutex(&socrates, clock);
	create_threads(&socrates, &clock->timer);
	join_threads(&socrates, &clock->timer);
	destroy_mutex(&socrates);
	free_philosopher(socrates);
	free(clock);
}

int	main(int argc, char **argv)
{
	int				number;
	t_philosopher	*socrates;
	t_timer			*clock;
	t_simulation	sim;

	if (argc == 5 || argc == 6)
	{
		clock = malloc(sizeof(t_timer));
		if (!clock)
			return (0); 
		sim.stop_simulation = 0;
		socrates = NULL;
		number = ft_atoi(argv[1]);
		sim.enough_counter = number;
		if (number > 1)
		{
			if (!gather_philosophers(&socrates, number, argv, argc))
				return (0);
		}
		else
			return (0);
		call_functions(socrates, clock, sim);
	}
	return (0);
}
