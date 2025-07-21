/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:32:23 by khkomasa          #+#    #+#             */
/*   Updated: 2025/07/17 16:19:26 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void assign_values(t_var *var, pthread_mutex_t *forks, int i)
{
	var->philos[i].id = i + 1;
	var->philos[i].first_fork = (i + 1) % var->num_of_philo;
	var->philos[i].second_fork = i;
	var->philos[i].meals_eaten = 0;
	var->philos[i].is_dead = &var->is_dead;
	var->philos[i].is_eating = 0;
	var->philos[i].start_timestamp = current_time_msec();
	var->philos[i].lastmeal_timestamp = current_time_msec();
	var->philos[i].time_to_die = var->time_to_die;
	var->philos[i].time_to_eat = var->time_to_eat;
	var->philos[i].time_to_sleep = var->time_to_sleep;
	var->philos[i].required_meals = var->required_meals;
	var->philos[i].num_of_philo = var->num_of_philo;
	var->philos[i].starttime_mutex = &var->starttime_mutex;
	var->philos[i].dead_mutex = &var->dead_mutex;
	var->philos[i].lastmeal_mutex = &var->lastmeal_mutex;
	var->philos[i].forks = &forks[i];
}

static void init_philos(t_var *var, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		assign_values(var, forks, i);
		i++;
	}
}

static void init_forks(pthread_mutex_t *forks, int philo_num)
{
	int i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void init_program(t_var *var, t_philo *philos)
{
	var->is_dead = 0;
	var->philos = philos;
	pthread_mutex_init(&var->starttime_mutex, NULL);
	pthread_mutex_init(&var->dead_mutex, NULL);
	pthread_mutex_init(&var->lastmeal_mutex, NULL);
}

int initialization(t_var *var, t_philo *philos, pthread_mutex_t *forks)
{
	init_program(var, philos);
	init_forks(forks, var->num_of_philo);
	init_philos(var, forks);
	create_threads(var);
	return (0);
}
