/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:18 by khkomasa          #+#    #+#             */
/*   Updated: 2025/08/01 04:23:31 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->num_of_philo)
	{
		if (pthread_join(var->philos[i].thread, NULL) != 0)
			error_exit(-1, "Failed to join thread");
		i++;
	}
	if (pthread_join(var->monitor->thread, NULL) != 0)
		error_exit(-1, "Failed to join thread");
	return (0);
}

static int	create_threads(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->num_of_philo)
	{
		if (pthread_create(&var->philos[i].thread, NULL, \
&philo_routine, &var->philos[i]) != 0)
			error_exit(-1, "Failed to created thread");
		i++;
	}
	if (pthread_create(&var->monitor->thread, NULL, \
&monitor_routine, var->philos) != 0)
		error_exit(-1, "Failed to created thread");
	return (0);
}

int	start_simulation(t_var *var)
{
	if (create_threads(var) < 0)
		return (-1);
	if (join_threads(var) < 0)
		return (-1);
	return (0);
}
