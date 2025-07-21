/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:32:51 by khkomasa          #+#    #+#             */
/*   Updated: 2025/07/17 15:45:41 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_forks(pthread_mutex_t *forks, int philo_num)
{
	int i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void init_program(t_var *var, t_philo *philos)
{
	var->is_dead = 0;
	var->philos = philos;
	pthread_mutex_init(&var->starttime_mutex, NULL);
	pthread_mutex_init(&var->dead_mutex, NULL);
	pthread_mutex_init(&var->lastmeal_mutex, NULL);
}

int main(int argc, char *argv[])
{
	t_var var;
	t_philo philos[MAX_PHILOS];
	pthread_mutex_t forks[MAX_PHILOS];

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&var, argc, argv) < 0)
			return (-1);
		init_program(&var, philos);
		init_forks(forks, var.num_of_philo);
		init_philos(&var, forks);
		create_threads(&var);
		// join_threads(&var);
		// if (initialization(&var) < 0)
		// 	return (-1);
		// start_simulation(&var);
		clean(&var, forks);
		// printf("main completed\n");
	}
	else
		return (error_exit(-1, "Invalid Input Agruments"));
	return (0);
}
