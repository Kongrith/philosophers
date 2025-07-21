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

// static int init_program_mutex(t_var *var)
// {
// 	if (pthread_mutex_init(&var->ready_mutex, NULL))
// 		return (error_exit(-1, "Can not initial ready mutex"));
// 	// if (pthread_mutex_init(&var->isdead_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->allready_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->starttime_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->time2die_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->deadindex_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->deathtime_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->time2eat_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->time2sleep_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	return (0);
// }

// static int init_philo_mutex(t_var *var, int i)
// {
// 	if (pthread_mutex_init(&var->forks[i], NULL))
// 		return (error_exit(-1, "Can not initial fork mutex"));
// 	// if (pthread_mutex_init(&var->, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->ready_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->philo[i].lastmeal_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->philo[i].remaining_meals_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	// if (pthread_mutex_init(&var->philo[i].id_mutex, NULL))
// 	// 	return (error_exit(-1, "Can not initial mutex"));
// 	return (0);
// }

// static int init_mutexes(t_var *var)
// {
// 	int i;

// 	i = 0;
// 	if (init_program_mutex(var) == -1)
// 		return (-1);
// 	while (i < var->num_of_philo)
// 	{
// 		if (init_philo_mutex(var, i) == -1)
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

void init_philos(t_var *var, pthread_mutex_t *forks)
{
	int i;
	// long start_timestamp;

	i = 0;
	// start_timestamp = current_time_msec();
	while (i < var->num_of_philo)
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
		// var->philos[i].var = var;
		i++;
	}
}

// int initialization(t_var *var)
// {
// 	var->is_dead = 0;
// 	var->dead_index = -1;
// 	// var->philo = malloc(sizeof(t_philo) * var->num_of_philo);
// 	// var->forks = malloc(sizeof(pthread_mutex_t) * var->num_of_philo);
// 	// var->monitor = malloc(sizeof(t_monitor));
// 	// if (var->philo == NULL || var->monitor == NULL || var->forks == NULL)
// 	// {
// 	// 	clean(var, 1);
// 	// 	return (error_exit(-1, "Can not reserve memory for malloc function\n"));
// 	// }
// 	if (init_mutexes(var) < 0)
// 	{
// 		clean(var, 2);
// 		return (-1);
// 	}
// 	init_philos(var);
// 	// if (init_mutexes(var) < 0)
// 	// {
// 	// 	clean(var, 2);
// 	// 	return (-1);
// 	// }
// 	// set_int(&var->allready_mutex, &var->all_threads_ready, 0);
// 	// set_int(var, 0, 0);
// 	// pthread_mutex_lock(&var->ready_mutex);
// 	// var->all_threads_ready = 0;
// 	// pthread_mutex_unlock(&var->ready_mutex);
// 	return (0);
// }
