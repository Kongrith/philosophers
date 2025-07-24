/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:17:30 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/21 22:54:38 by khkomasa         ###   ########.fr       */
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
		fork = var->philos[i].second_fork;
		pthread_mutex_destroy(fork);
		i++;
	}
	pthread_mutex_destroy(&var->starttime_mutex);
	pthread_mutex_destroy(&var->dead_mutex);
	pthread_mutex_destroy(&var->lastmeal_mutex);
}
