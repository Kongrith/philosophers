/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khkomasa <khkomasa@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:18 by khkomasa          #+#    #+#             */
/*   Updated: 2025/02/24 01:33:29 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *philo_routine(void *data)
{
	t_philo *philo;
	long msec;

	philo = (t_philo *)data;
	msec = get_time_in_ms() - philo->var->start_time;
	// printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, phil->pos, "has taken a fork");
	printf("%.6ld %d has taken a fork\n", msec, philo->id);
	return (0);
}

static void create_mutexes(t_var *var)
{
	int i;

	i = 0;
	var->start_time = get_time_in_ms();
	while (i < var->num_of_philo)
	{
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
	create_mutexes(var);
	join_mutexes(var);
	if (var->is_dead == 1)
		printf("%ld %d %s\n", get_time_in_ms() - var->start_time, var->dead_index, "died");
	return (0);
}
