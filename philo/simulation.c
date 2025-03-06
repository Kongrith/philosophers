/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:18 by khkomasa          #+#    #+#             */
/*   Updated: 2025/03/05 18:42:43 by toon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *philo_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->var->num_of_philo == 1)
		lone_philo(philo);
	else
	{
		// if (philo->id % 2 == 0)
		// 	usleep(200);
			// printf("id: %d sleep 200 usec\n", philo->id);
		even_odd_approach(philo);
	}
	return (NULL);
}

static void create_threads(t_var *var)
{
	int i;

	i = 0;
	// var->start_time = timestamp_in_ms();
	while (i < var->num_of_philo)
	{
		// var->philo[i].last_meal_time = timestamp_in_ms();
		if (pthread_create(&var->philo[i].thread, NULL, &philo_routine, &var->philo[i]) != 0)
			error_exit("Failed to created thread");
		i++;
	}
	if (pthread_create(&var->monitor->thread, NULL, &monitor, var) != 0)
		error_exit("Failed to created thread");
}

static void join_mutexes(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{

		if (pthread_join(var->philo[i].thread, NULL) != 0)
			error_exit("Failed to join thread");
		i++;
	}
	if (pthread_join(var->monitor->thread, NULL)!= 0)
		error_exit("Failed to join thread");
}

int start_simulation(t_var *var)
{
	create_threads(var);
	var->start_time = timestamp_in_ms();
	var->all_threads_ready = 1;
	join_mutexes(var);
	if (var->is_dead)
	{
		printf("%.3ld %d died\n", var->time_of_death, var->dead_index);
	}
	return (0);
}
