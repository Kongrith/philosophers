/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:18 by khkomasa          #+#    #+#             */
/*   Updated: 2025/03/06 14:29:48 by toon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *monitor_routine(void *data)
{
	int i;
	t_var *var;
	// time_t spent_time;

	var = (t_var *)data;
	wait_all_threads(var);
	usleep(get_long(&var->time2die_mutex, var->time_to_die) * 1000 * 0.5);
	while (!get_int(&var->isdead_mutex, var->is_dead))
	{
		i = 0;
		while ((i < var->num_of_philo) && (!get_int(&var->isdead_mutex, var->is_dead)))
		{
			// spent_time = timestamp_in_ms() - get_timestamp(&var->philo->lastmeal_mutex, var->philo->last_meal_timestamp);
			if (timestamp_in_ms() - get_timestamp(&var->philo->lastmeal_mutex, var->philo->last_meal_timestamp) >= get_long(&var->time2die_mutex, var->time_to_die))
			{
				// var->death_time = timestamp_in_ms() - get_timestamp(&var->starttime_mutex, var->start_timestamp);
				set_long(&var->deathtimestamp_mutex, &var->death_time, timestamp_in_ms() - get_timestamp(&var->starttime_mutex, var->start_timestamp));
				set_int(&var->deadindex_mutex, &var->dead_index, i + 1);
				set_int(&var->isdead_mutex, &var->is_dead, 1);
			}
			i++;
		}
	}
	return (NULL);
}

static void *philo_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->var->num_of_philo == 1)
		lone_philo(philo);
	else
		even_odd_approach(philo);
	return (NULL);
}

static void create_threads(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		if (pthread_create(&var->philo[i].thread, NULL, &philo_routine, &var->philo[i]) != 0)
			error_exit(-1, "Failed to created thread");
		i++;
	}
	if (pthread_create(&var->monitor->thread, NULL, &monitor_routine, var) != 0)
		error_exit(-1, "Failed to created thread");
}

static void join_threads(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{

		if (pthread_join(var->philo[i].thread, NULL) != 0)
			error_exit(-1, "Failed to join thread");
		i++;
	}
	if (pthread_join(var->monitor->thread, NULL) != 0)
		error_exit(-1, "Failed to join thread");
}

int start_simulation(t_var *var)
{
	set_timestamp(&var->starttime_mutex, &var->start_timestamp, timestamp_in_ms());
	set_int(&var->allready_mutex, &var->all_threads_ready, 1);
	create_threads(var);
	// set_timestamp(&var->starttime_mutex, &var->start_timestamp, timestamp_in_ms());
	// set_int(&var->allready_mutex, &var->all_threads_ready, 1);

	// set_int(&var->wait, &var->all_threads_ready, 0);
	// var->start_timestamp = timestamp_in_ms();
	// pthread_mutex_lock(&var->wait);
	// (var->all_threads_ready)++;
	// pthread_mutex_unlock(&var->wait);
	join_threads(var);

	// get_int(&var->die_mutex, &var->is_dead)
	if (get_int(&var->isdead_mutex, var->is_dead))
		write_status(DIED, var->philo, DEBUG_MODE);
	return (0);
}
