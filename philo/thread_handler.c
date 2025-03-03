/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:18 by khkomasa          #+#    #+#             */
/*   Updated: 2025/03/03 13:25:41 by toon             ###   ########.fr       */
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
		if (philo->id % 2 == 0)
			usleep(200);
			// printf("id: %d sleep 200 usec\n", philo->id);
		even_odd_approach(philo);
	}
	return (NULL);
}

static void create_threads(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		var->philo[i].last_meal_time = get_time_in_ms();
		if (pthread_create(&var->philo[i].thread, NULL, &philo_routine, &var->philo[i]) != 0)
			error_exit("Failed to created thread");
		// printf("Thread: %d starting ..\n", i);
		i++;
	}
	// printf("created mutexes\n");
	pthread_create(&var->monitor->thread, NULL, &monitor, var);
	i = 0;
	// printf("num_of_philo: %d\n", var->num_of_philo);

	while (i < var->num_of_philo)
	{
		// printf("i:%d\n", i);
		if (pthread_join(var->philo[i].thread, NULL) != 0)
			error_exit("Failed to join thread");
		// printf("Thread: %d ending ..\n", i);
		i++;
	}
	// i = -1;
	// while (++i < var->num_of_philo)
	// 	pthread_join(var->philo[i].thread, NULL);
	// printf("%d\n", i);
	// if (pthread_create(&var->monitor->thread, NULL, &monitor, var) != 0)
	// 	error_exit("Failed to created thread");
	// printf("i after threads:%d\n", i);
	printf("finish monitor\n");
}

// static void join_mutexes(t_var *var)
// {
// 	int i;

// 	i = 0;
// 	while (i < var->num_of_philo)
// 	{
// 		printf("%d\n", i);
// 		if (pthread_join(var->philo[i].thread, NULL) != 0)
// 			error_exit("Failed to join thread");
// 		i++;
// 	}
// 	// if (pthread_join(var->monitor, NULL) != 0)
// 	// 	error_exit("Failed to join thread");

// }

int start_simulation(t_var *var)
{
	var->start_time = get_time_in_ms();		// start time of simulation
	create_threads(var);
	printf("out from mutexes\n");
	// join_mutexes(var);
	printf("joined mutexes\n");
	if (var->is_dead)
	{
		printf("###\n");
		// elapsed_time = get_time_in_ms() - var->start_time;
		printf("%.6ld %d died\n", var->time_of_death, var->dead_index);
		// write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	}

		// printf("%ld %d %s\n", get_time_in_ms() - var->start_time, var->dead_index, "died");
	return (0);
}
