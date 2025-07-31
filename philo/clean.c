/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:17:30 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/26 03:12:16 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean(t_var *var)
{
	int i;
	pthread_mutex_t *fork;

	i = 0;
	while (i < var->num_of_philo)
	{
		fork = &var->forks[i];
		pthread_mutex_destroy(fork);
		i++;
	}
	pthread_mutex_destroy(&var->starttime_mutex);
	pthread_mutex_destroy(&var->finish_mutex);
	pthread_mutex_destroy(&var->lastmeal_mutex);
	if (var->forks)
		free(var->forks);
	if (var->philos)
		free(var->philos);
	if (var->monitor)
		free(var->monitor);
}
