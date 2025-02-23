/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:07 by khkomasa          #+#    #+#             */
/*   Updated: 2025/02/24 02:35:37 by toon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>	// printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <stdbool.h>
# include <pthread.h> // mutex: init destroy lock unlock, threadL create join detach
# include <sys/time.h> // gettimeofday
# include <limits.h>	  // INT_MAX

typedef struct s_var t_var;
typedef struct s_philo
{
	int id;
	int first_fork;
	int second_fork;
	long last_meal_time;
	t_var *var;
	pthread_t thread;
} t_philo;

typedef struct s_var
{
	int num_of_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int limit_meals;
	int is_dead;
	int dead_index;
	time_t start_time;
	time_t time_of_death;
	t_philo *philo;
	pthread_mutex_t *forks;
} t_var;


// init.c
void initialization(t_var *var);

// parse input
void parse_input(t_var *var, int argc, char *argv[]);

// sim.c
int start_simulation(t_var *var);

// utils.c
void error_exit(char *str);
time_t get_time_in_ms();

#endif
