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

void clean(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		pthread_mutex_destroy(var->philos[i].forks);
		i++;
	}
	pthread_mutex_destroy(&var->starttime_mutex);
	pthread_mutex_destroy(&var->dead_mutex);
	pthread_mutex_destroy(&var->lastmeal_mutex);
}
