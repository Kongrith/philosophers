/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:32:23 by khkomasa          #+#    #+#             */
/*   Updated: 2025/03/06 14:15:37 by toon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int init_mutexes(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		if (pthread_mutex_init(&var->forks[i], NULL))
			return (error_exit(-1, "Can not initial mutex"));
		if (pthread_mutex_init(&var->philo[i].lastmeal_mutex, NULL))
			return (error_exit(-1, "Can not initial mutex"));
		i++;
	}

	if (pthread_mutex_init(&var->isdead_mutex, NULL))
		return (error_exit(-1, "Can not initial mutex"));
	if (pthread_mutex_init(&var->allready_mutex, NULL))
		return (error_exit(-1, "Can not initial mutex"));
	if (pthread_mutex_init(&var->starttime_mutex, NULL))
		return (error_exit(-1, "Can not initial mutex"));
	if (pthread_mutex_init(&var->time2die_mutex, NULL))
		return (error_exit(-1, "Can not initial mutex"));
	if (pthread_mutex_init(&var->deadindex_mutex, NULL))
		return (error_exit(-1, "Can not initial mutex"));
	if (pthread_mutex_init(&var->deathtimestamp_mutex, NULL))
		return (error_exit(-1, "Can not initial mutex"));

	// 	pthread_mutex_t deadindex_mutex;	  // start time
	// pthread_mutex_t deathtimestamp_mutex; // start time
	return (0);
}

static void init_philos(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		var->philo[i].id = i + 1;
		var->philo[i].first_fork = (i + 1) % var->num_of_philo;
		var->philo[i].second_fork = i;
		var->philo[i].remaining_meals = var->required_meals;
		var->philo[i].var = var;
		i++;
	}
}

int initialization(t_var *var)
{
	var->is_dead = 0;
	var->dead_index = -1;
	var->philo = malloc(sizeof(t_philo) * var->num_of_philo);
	var->monitor = malloc(sizeof(t_monitor));
	var->forks = malloc(sizeof(pthread_mutex_t) * var->num_of_philo);
	if (var->philo == NULL || var->monitor == NULL || var->forks == NULL)
	{
		clean(var, 1);
		return (error_exit(-1, "Can not reserve memory for malloc function\n"));
	}
	init_philos(var);
	if (init_mutexes(var) < 0)
		return (-1);
	set_int(&var->allready_mutex, &var->all_threads_ready, 0);
	return (0);
}
