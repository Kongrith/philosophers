/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:17:30 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/17 15:45:24 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void destroy_mutex(t_var *var, pthread_mutex_t *forks)
{
	int i;

	(void)forks;
	i = 0;
	while (i < var->num_of_philo)
	{
		// pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(var->philos[i].forks);

		// pthread_mutex_destroy(&var->philos[i].forks[i]);

		// pthread_mutex_destroy(&var->philos[i].forks[i]);
		// pthread_mutex_destroy(&var->philo[i].lastmeal_mutex);
		// pthread_mutex_destroy(&var->philo[i].remaining_meals_mutex);
		// pthread_mutex_destroy(&var->philo[i].id_mutex);
		i++;
	}

	// while (i < program->philos[0].num_of_philos)
	// {
	// 	pthread_mutex_destroy(&forks[i]);
	// 	i++;
	// }

	pthread_mutex_destroy(&var->starttime_mutex);
	pthread_mutex_destroy(&var->dead_mutex);
	pthread_mutex_destroy(&var->lastmeal_mutex);

	// pthread_mutex_destroy(&var->allready_mutex);
	// pthread_mutex_destroy(&var->starttime_mutex);
	// pthread_mutex_destroy(&var->isdead_mutex);
	// pthread_mutex_destroy(&var->time2die_mutex);
	// pthread_mutex_destroy(&var->deadindex_mutex);
	// pthread_mutex_destroy(&var->deathtime_mutex);
	// pthread_mutex_destroy(&var->time2eat_mutex);
	// pthread_mutex_destroy(&var->time2sleep_mutex);
}

void clean(t_var *var, pthread_mutex_t *fork)
{
	// if (level == 2)
	destroy_mutex(var, fork);
	// free(var->forks);
	// free(var->philo);
	// free(var->monitor);
}
