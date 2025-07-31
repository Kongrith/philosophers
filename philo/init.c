/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:32:23 by khkomasa          #+#    #+#             */
/*   Updated: 2025/07/26 03:13:33 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void assign_values(t_var *var, int i)
{
	var->philos[i].meals_eaten = 0;
	var->philos[i].is_finish = &var->is_finish;
	var->philos[i].is_eating = 0;
	var->philos[i].start_timestamp = current_time_msec();
	var->philos[i].lastmeal_timestamp = current_time_msec();
	var->philos[i].time_to_die = var->time_to_die;
	var->philos[i].time_to_eat = var->time_to_eat;
	var->philos[i].time_to_sleep = var->time_to_sleep;
	var->philos[i].required_meals = var->required_meals;
	var->philos[i].num_of_philo = var->num_of_philo;
	var->philos[i].starttime_mutex = &var->starttime_mutex;
	var->philos[i].finish_mutex = &var->finish_mutex;
	var->philos[i].lastmeal_mutex = &var->lastmeal_mutex;
}

static void init_philos(t_var *var, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		var->philos[i].id = i + 1;
		if (var->philos[i].id % 2 == 0)
		{
			var->philos[i].first_fork = &forks[i];
			var->philos[i].second_fork = &forks[(i + 1) % var->num_of_philo];
		}
		else
		{
			var->philos[i].first_fork = &forks[(i + 1) % var->num_of_philo];
			var->philos[i].second_fork = &forks[i];
		}
		assign_values(var, i);
		i++;
	}
}

static int init_forks(pthread_mutex_t *forks, int philo_num)
{
	int i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (error_exit(-1, "Can not initial fork mutex"));
		i++;
	}
	return (0);
}

int initialization(t_var *var)
{
	var->is_finish = 0;
	var->philos = malloc(sizeof(t_philo) * var->num_of_philo);
	var->monitor = malloc(sizeof(t_monitor));
	var->forks = malloc(sizeof(pthread_mutex_t) * var->num_of_philo);
	if (pthread_mutex_init(&var->starttime_mutex, NULL))
		return (error_exit(-1, "Can not initial start time mutex"));
	if (pthread_mutex_init(&var->finish_mutex, NULL))
		return (error_exit(-1, "Can not initial finish mutex"));
	if (pthread_mutex_init(&var->lastmeal_mutex, NULL))
		return (error_exit(-1, "Can not initial last meal mutex"));
	if (init_forks(var->forks, var->num_of_philo) < 0)
		return (-1);
	init_philos(var, var->forks);
	return (0);
}
