/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:27:28 by rhoogend          #+#    #+#             */
/*   Updated: 2025/10/30 11:44:38 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	child_proces(t_philosopher *philosopher, 
		t_sems *semaphores, t_timer *clock)
{
	pthread_create(&clock->time, NULL, timer, philosopher);
	while (1)
	{
		sem_wait(semaphores->tableforks);
		sem_wait(semaphores->tableforks);
		eat(philosopher, semaphores);
		sem_post(semaphores->tableforks);
		sem_post(semaphores->tableforks);
		if (!check_enough(philosopher))
		{
			free(philosopher);
			exit(0);
		}
		sleeping(philosopher, semaphores);
		thinking(philosopher, semaphores);
	}
	free(philosopher);
	exit(1);
}

void	free_all(t_sems *semaphores, t_timer *clock, int *pids)
{
	free(semaphores);
	free(clock);
	free(pids);
}

void	waiting(int number, int *pids, t_sems *semaphores, t_timer *clock)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	j = 0;
	while (i < number)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			while (j < number)
			{
				kill(pids[j], SIGTERM);
				j++;
			}
		}
		i++;
	}
	sem_close(semaphores->tableforks);
	sem_close(semaphores->print);
	sem_close(semaphores->stop);
	free_all(semaphores, clock, pids);
}

void	forking(int number, t_sems *semaphores, int argc, char **argv)
{
	int				*pids;
	int				pid;
	int				i;
	t_philosopher	*philosopher;
	t_timer			*clock;

	i = -1;
	clock = malloc(sizeof(t_timer));
	pids = malloc(sizeof(int) * number);
	while (++i < number)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("fork unssucesfull");
			exit(1);
		}
		if (pid == 0)
		{
			philosopher = create_philosopher(i + 1, argv, argc, semaphores);
			child_proces(philosopher, semaphores, clock);
		}
		pids[i] = pid;
	}
	waiting(number, pids, semaphores, clock);
}

static void	create_process(int number, int argc, char **argv)
{
	t_sems			*semaphores;

	semaphores = malloc(sizeof (t_sems));
	sem_unlink("/sem_1");
	sem_unlink("/print");
	sem_unlink("/stop");
	semaphores->tableforks = sem_open("/sem_1", O_CREAT, 0777, number);
	semaphores->print = sem_open("/print", O_CREAT, 0777, 1);
	semaphores->stop = sem_open("/stop", O_CREAT, 0777, 1);
	forking(number, semaphores, argc, argv);
}

int	main(int argc, char **argv)
{
	int				number;

	number = 0;
	if (argc == 5 || argc == 6)
	{
		number = ft_atoi(argv[1]);
		if (number > 1)
			create_process(number, argc, argv);
	}
	return (0);
}
