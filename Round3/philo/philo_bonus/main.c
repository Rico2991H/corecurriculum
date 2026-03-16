/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:27:28 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/22 10:53:47 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

/*static void	init_clock(t_philosopher *head, t_timer *clock)
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
}*/


void	*timer(void *head)
{
	struct timeval	t_current;
	t_philosopher	*temp;
	long			timestamp;
	int				counter = 0;

	temp = (t_philosopher *)head;
	sem_wait(temp->clock->dying);
	sem_wait(temp->clock->enough);
	while (!temp->pt_to_stop->stop_simulation 
		&& temp->pt_to_stop->enough_counter != 0)
	{
		sem_post(temp->clock->dying);
		sem_post(temp->clock->enough);
		usleep(temp->time_to_die / 2 * 1000);
		gettimeofday(&t_current, NULL);
		timestamp = (t_current.tv_sec * 1000L + t_current.tv_usec / 1000l);
		check_for_death(temp, head, timestamp);
		counter++;
		if(counter == 4)
			temp->pt_to_stop->stop_simulation = 1;
		temp = (t_philosopher *)head;
		sem_wait(temp->clock->dying);
		sem_wait(temp->clock->enough);		
	}
	return (NULL);
}


t_philosopher *retrieve_philosopher(int i, t_philosopher *socrates)
{
	t_philosopher *temp;

	temp = socrates;
	while(temp->next != socrates)
	{
		if ( i == temp->philosopher_nb)
			return (temp);
		temp = temp->next;
	}
	if (temp->next == socrates)
	{
		if ( i == temp->philosopher_nb)
			return (temp);
	}
	return (socrates);
}


static void	create_process(int number, t_simulation sim, t_philosopher *socrates)
{
	t_timer			*clock;
	sem_t			*tableforks;
	int				pid;
	int				*pids;
	int				i;
	t_philosopher	*philosopher;
	
	sim.stop_simulation = 0;
	i = 1;
	pids = malloc(sizeof(int) * number);
	clock = malloc(sizeof(t_timer));
	sem_unlink("/sem_1");
	tableforks = sem_open("/sem_1", O_CREAT, 0777, number);
	pid = 1;
	init_sim(socrates, &sim);
	while (i <= number)
	{
		pid = fork();
		if (pid == -1)
		{
		printf("fork unssucesfull");
		exit(1);
		}
		if (pid == 0)
		{
			philosopher = retrieve_philosopher(i, socrates);
			break;
		}
		pids[i] = pid;
		i++;
	}
	if (pid == 0)
	{
		//while (!philosopher->pt_to_stop->stop_simulation 
		//&& philosopher->pt_to_stop->enough_counter != 0)
		//{
			sem_wait(tableforks);
			sem_wait(tableforks);
			eat(philosopher);
			sem_post(tableforks);
			sem_post(tableforks);
			sleeping(philosopher);
			thinking(philosopher);
		//}
		free_philosopher(socrates);
		exit(0);
	}
	else
	{		
	sem_unlink("/sem_2");
	clock->enough = sem_open("/sem_2", O_CREAT, 0777, 1);
	sem_unlink("/sem_3");
	clock->dying = sem_open("/sem_3", O_CREAT, 0777, 1);
	pthread_create(&clock->time, NULL, timer, socrates);
	int	status;
	i = 0;
	while (i < number)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	sem_close(tableforks);
	}
}

int	main(int argc, char **argv)
{
	int				number;
	t_philosopher	*socrates;
	t_simulation	sim;

	sim.stop_simulation = 0;
	socrates = NULL;
	number = 0;
	if (argc == 5 || argc == 6)
	{
		number = ft_atoi(argv[1]);
		if (number > 1)
		{
			if (!gather_philosophers(&socrates, number, argv, argc))
				return (0);
			create_process(number, sim, socrates);
		}
	}
	return (0);
}
