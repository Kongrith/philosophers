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

static void	destroy_mutex(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->num_of_philo)
	{
		pthread_mutex_destroy(&var->forks[i]);
		pthread_mutex_destroy(&var->philo[i].lastmeal_mutex);
		pthread_mutex_destroy(&var->philo[i].remaining_meals_mutex);
		pthread_mutex_destroy(&var->philo[i].id_mutex);
		i++;
	}
	pthread_mutex_destroy(&var->allready_mutex);
	pthread_mutex_destroy(&var->starttime_mutex);
	pthread_mutex_destroy(&var->isdead_mutex);
	pthread_mutex_destroy(&var->time2die_mutex);
	pthread_mutex_destroy(&var->deadindex_mutex);
	pthread_mutex_destroy(&var->deathtime_mutex);
	pthread_mutex_destroy(&var->time2eat_mutex);
	pthread_mutex_destroy(&var->time2sleep_mutex);
}

void	clean(t_var *var, int level)
{
	if (level == 2)
		destroy_mutex(var);
	free(var->forks);
	free(var->philo);
	free(var->monitor);
}
