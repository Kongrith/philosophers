/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:18 by khkomasa          #+#    #+#             */
/*   Updated: 2025/02/24 03:41:46 by toon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void *lone_philo(void *arg)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)arg;
// 	wait_all_threads(philo->table);
// 	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
// 	increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
// 	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
// 	while (!simulation_finished(philo->table))
// 		usleep(200);
// 	return (NULL);
// }

void lone_philo(t_philo *philo)
{
	long elapsed_time;

	pthread_mutex_lock(&philo->var->forks[philo->first_fork]);
	elapsed_time = get_time_in_ms() - philo->var->start_time;
	// printf("start:%ld\n", philo->var->start_time);
	// printf("elapsed_time:%ld\n", elapsed_time);
	// printf("time to die: %ld\n", philo->var->time_to_die);

	printf("%.6ld %d has taken a fork\n", elapsed_time, philo->id);
	while (1)
	{
		// printf("elapse time: %ld\n", get_time_in_ms() - philo->last_meal_time);
		if (get_time_in_ms() - philo->last_meal_time > philo->var->time_to_die)
		{
			philo->var->time_of_death = get_time_in_ms() - philo->var->start_time;
			philo->var->dead_index = philo->id;
			philo->var->is_dead = 1;
			break;
		}
	}
}

static void *philo_routine(void *data)
{
	t_philo *philo;
	// long msec;

	philo = (t_philo *)data;
	// msec = get_time_in_ms() - philo->var->start_time;

	if (philo->var->num_of_philo == 1)
	{
		lone_philo(philo);
		return (NULL);
	}
	else
	{
		// printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, phil->pos, "has taken a fork");
		// printf("%.6ld %d has taken a fork\n", msec, philo->id);
	}
	return (0);
}

static void create_mutexes(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		var->philo[i].last_meal_time = get_time_in_ms();
		if (pthread_create(&var->philo[i].thread, NULL, &philo_routine, &var->philo[i]) != 0)
			error_exit("Failed to created thread");
		i++;
	}
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
}

int start_simulation(t_var *var)
{
	// long elapsed_time;
	var->start_time = get_time_in_ms();
	// printf("%ld\n", var->start_time);
	create_mutexes(var);
	join_mutexes(var);
	if (var->is_dead == 1)
	{
		// elapsed_time = get_time_in_ms() - var->start_time;
		printf("%.6ld %d died\n", var->time_of_death, var->dead_index);
	}

		// printf("%ld %d %s\n", get_time_in_ms() - var->start_time, var->dead_index, "died");
	return (0);
}
