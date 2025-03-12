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

static void init_mutexes(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		if (pthread_mutex_init(&var->forks[i], NULL))
			error_exit(-1, "Can not init mutex");
		i++;
	}
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

void initialization(t_var *var)
{
	var->is_dead = 0;
	var->dead_index = -1;
	var->philo = malloc(sizeof(t_philo) * var->num_of_philo);
	var->monitor = malloc(sizeof(t_monitor));
	var->forks = malloc(sizeof(pthread_mutex_t) * var->num_of_philo);
	var->all_threads_ready = 0;
	init_philos(var);
	init_mutexes(var);
}
