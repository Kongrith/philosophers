/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:07 by khkomasa          #+#    #+#             */
/*   Updated: 2025/08/01 04:20:21 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define DEBUG_MODE false

typedef struct s_var	t_var;

typedef struct s_monitor
{
	pthread_t	thread;
}	t_monitor;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				*is_finish;
	int				is_eating;
	long			start_timestamp;
	long			lastmeal_timestamp;
	int				num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				required_meals;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	*starttime_mutex;
	pthread_mutex_t	*finish_mutex;
	pthread_mutex_t	*lastmeal_mutex;
}	t_philo;

typedef struct s_var
{
	int				num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				required_meals;
	int				is_finish;
	t_philo			*philos;
	t_monitor		*monitor;
	time_t			start_timestamp;
	pthread_mutex_t	*forks;
	pthread_mutex_t	starttime_mutex;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t	lastmeal_mutex;
}	t_var;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
	FULL,
}	t_philo_status;

// parse input
int		parse_input(t_var *var, int argc, char *argv[]);

// init.c
int		initialization(t_var *var);

// simulation.c
int		start_simulation(t_var *var);

// thread_handler.c
void	*philo_routine(void *data);

// thread_handler_utikls.c
int		stoping_criteria(t_philo *philo);

// monitor.c
void	*monitor_routine(void *data);

// utils.c
time_t	current_time_msec(void);
int		precise_sleep(size_t milliseconds);
int		error_exit(int err_code, char *str);
void	write_status(t_philo_status status, t_philo *philo, bool debug);

// clean.c
void	clean(t_var *var);
int		precise_sleep(size_t milliseconds);
#endif
