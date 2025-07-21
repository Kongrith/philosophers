/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:07 by khkomasa          #+#    #+#             */
/*   Updated: 2025/07/17 17:09:11 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

#define DEBUG_MODE false
#define MAX_PHILOS 210

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
	int meals_eaten;
	int *is_dead;
	int is_eating;
	long start_timestamp;
	long lastmeal_timestamp;
	int num_of_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int required_meals;
	pthread_t thread;
	pthread_mutex_t *starttime_mutex;
	pthread_mutex_t *dead_mutex;
	pthread_mutex_t *lastmeal_mutex;
	pthread_mutex_t *forks;
} t_philo;

typedef struct s_var
{
	int num_of_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int required_meals;
	int is_dead;
	time_t start_timestamp;
	t_philo *philos;
	pthread_mutex_t starttime_mutex;
	pthread_mutex_t dead_mutex;
	pthread_mutex_t lastmeal_mutex;
} t_var;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
} t_philo_status;

// parse input
int parse_input(t_var *var, int argc, char *argv[]);

// init.c
int initialization(t_var *var, t_philo *philos, pthread_mutex_t *forks);

// simulation.c
int start_simulation(t_var *var);

// thread_handler.c
void *philo_routine(void *data);

// thread_handler_utikls.c
int stoping_criteria(t_philo *philo);

// monitor.c
void *monitor_routine(void *data);

// utils.c
time_t current_time_msec(void);
int precise_sleep(size_t milliseconds);
int error_exit(int err_code, char *str);
void write_status(t_philo_status status, t_philo *philo, int id, bool debug);

// clean.c
void clean(t_var *var);
int precise_sleep(size_t milliseconds);
#endif
