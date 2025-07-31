/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:32:51 by khkomasa          #+#    #+#             */
/*   Updated: 2025/07/26 03:19:29 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_var			var;
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&var, argc, argv) < 0)
			return (-1);
		if (initialization(&var, philos, forks) < 0)
		{
			clean(&var);
			return (-1);
		}
		start_simulation(&var);
		clean(&var);
	}
	else
		return (error_exit(-1, "Invalid Input Agruments"));
	return (0);
}
