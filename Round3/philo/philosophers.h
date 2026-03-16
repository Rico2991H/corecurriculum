/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:06:28 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/17 13:36:50 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_simulation
{
	volatile int	stop_simulation;
	volatile int	enough_counter;
}				t_simulation;

typedef struct s_timer
{
	pthread_t				timer;
	pthread_mutex_t			stop_mutex;
	pthread_mutex_t			print_mutex;
}	t_timer;

typedef struct s_philosopher
{
	unsigned int			time_to_eat;
	long					time_to_die;
	long					last_eat;
	unsigned int			time_to_sleep;
	int						number_of_times;
	unsigned int			philosopher_nb;
	pthread_t				thread;
	pthread_mutex_t			mutex;
	pthread_mutex_t			eat_mutex;
	t_simulation			*pt_to_stop;
	t_timer					*clock;
	struct s_philosopher	*next;
}	t_philosopher;

int		gather_philosophers(t_philosopher **socrates, 
			int nb, char **args, int argc);
int		ft_atoi(const char *nptr);
void	create_threads(t_philosopher **socrates, pthread_t *time);
void	init_mutex(t_philosopher **socrates, t_timer *clock);
void	destroy_mutex(t_philosopher **socrates);
void	join_threads(t_philosopher **socrates, pthread_t *time);
void	*eat(t_philosopher *head);
void	sleeping(t_philosopher *head);
void	thinking(t_philosopher *head);
void	dying(long timestamp, t_philosopher *head);
void	*join_table(void *head);
void	free_philosopher(t_philosopher *socrates);
int		check_enough(t_philosopher *temp);
void	check_for_death(t_philosopher *temp, 
			t_philosopher *head, long timestamp);
void	check_for_forks(t_philosopher *temp);

#endif