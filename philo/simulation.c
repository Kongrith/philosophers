/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:18 by khkomasa          #+#    #+#             */
/*   Updated: 2025/07/21 22:52:11 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_and_join_threads(t_var *var)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitor_routine, var->philos) != 0)
		error_exit(-1, "Failed to created thread");
	while (i < var->num_of_philo)
	{
		if (pthread_create(&var->philos[i].thread, NULL, &philo_routine, \
&var->philos[i]) != 0)
			error_exit(-1, "Failed to created thread");
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		error_exit(-1, "Failed to join thread");
	while (i < var->num_of_philo)
	{
		if (pthread_join(var->philos[i].thread, NULL) != 0)
			error_exit(-1, "Failed to join thread");
		i++;
	}
	return (0);
}

int	start_simulation(t_var *var)
{
	if (create_and_join_threads(var) < 0)
		return (-1);
	return (0);
}
