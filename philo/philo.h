/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:07 by khkomasa          #+#    #+#             */
/*   Updated: 2025/03/06 14:30:10 by toon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>	// printf
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, usleep
#include <stdbool.h>
#include <pthread.h>  // mutex: init destroy lock unlock, threadL create join detach
#include <sys/time.h> // gettimeofday
#include <limits.h>	  // INT_MAX

#define DEBUG_MODE false

typedef struct s_var t_var;

typedef struct s_monitor
{
	pthread_t thread;
} t_monitor;

typedef struct s_philo
{
	int id;
	int first_fork;
	int second_fork;
	int remaining_meals;
	time_t last_meal_timestamp;
	t_var *var;
	pthread_t thread;
	pthread_mutex_t lastmeal_mutex;		   // timestampt for lastmeal time
	pthread_mutex_t remaining_meals_mutex; // timestampt for lastmeal time
	pthread_mutex_t id_mutex;			   // timestampt for lastmeal time
} t_philo;

typedef struct s_var
{
	int num_of_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int required_meals;
	int is_dead;
	int dead_index;
	int all_threads_ready;
	time_t start_timestamp;
	time_t death_time;
	t_philo *philo;
	t_monitor *monitor;
	pthread_mutex_t *forks;
	pthread_mutex_t allready_mutex;
	pthread_mutex_t isdead_mutex;
	pthread_mutex_t starttime_mutex;
	pthread_mutex_t time2die_mutex;
	pthread_mutex_t time2eat_mutex;
	pthread_mutex_t time2sleep_mutex;
	pthread_mutex_t deadindex_mutex;
	pthread_mutex_t deathtime_mutex;
} t_var;

typedef enum
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
} t_philo_status;

// init.c
int initialization(t_var *var);

// parse input
int parse_input(t_var *var, int argc, char *argv[]);

// thread_handler.c
int start_simulation(t_var *var);
void wait_all_threads(t_var *var);

// simulation.c
void lone_philo(t_philo *philo);
void even_odd_approach(t_philo *philo);

// utils.c
int error_exit(int err_code, char *str);
time_t timestamp_in_ms();
void write_status(t_philo_status status, t_philo *philo, bool debug);

//
int get_int(pthread_mutex_t *mutex, int value);
void set_int(pthread_mutex_t *mutex, int *dest, int value);
time_t get_timestamp(pthread_mutex_t *mutex, time_t value);
void set_timestamp(pthread_mutex_t *mutex, time_t *dest, time_t value);
long get_long(pthread_mutex_t *mutex, long value);
void set_long(pthread_mutex_t *mutex, long *dest, long value);

// clean.c
void clean(t_var *var, int level);

#endif
