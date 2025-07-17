/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:19:42 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/17 15:19:44 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void wait_all_threads(t_var *var)
{
	while (!get_int(&var->allready_mutex, var->all_threads_ready))
		;
}

void lone_philo(t_philo *philo)
{
	wait_all_threads(philo->var);
	set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp, timestamp_in_ms());
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (1)
	{
		if (timestamp_in_ms() - get_timestamp(&philo->lastmeal_mutex, philo->last_meal_timestamp) > get_long(&philo->var->time2die_mutex, philo->var->time_to_die))
		{
			// set_long(&philo->var->deathtimestamp_mutex, &philo->var->death_time, timestamp_in_ms() - get_timestamp(&philo->var->starttime_mutex, philo->var->start_timestamp));
			// set_int(&philo->var->deadindex_mutex, &philo->var->dead_index, 1);
			// set_int(&philo->var->isdead_mutex, &philo->var->is_dead, 1);
			// pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
			break;
		}
	}
}

void even_odd_approach(t_philo *philo)
{
	// int count;

	wait_all_threads(philo->var);
	// philo->last_meal_timestamp = timestamp_in_ms();
	set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp, timestamp_in_ms());
	// if (philo->id % 2)
	if (get_int(&philo->id_mutex, philo->id) % 2 == 0)
		usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000 * 0.5);
	else if (get_int(&philo->id_mutex, philo->id) == philo->var->num_of_philo)
	{
		usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000 * 0.6);
	}

	// usleep(philo->var->time_to_eat * 1000 * 0.5);

	// if (philo->remaining_meals == -1)
	// 	count = -1;
	// else
	// 	count = philo->remaining_meals;
	// while (count && (!philo->var->is_dead))
	// while (philo->remaining_meals && (!get_int(&philo->var->isdead_mutex, philo->var->is_dead)))
	while (get_int(&philo->remaining_meals_mutex, philo->remaining_meals) && (!get_int(&philo->var->isdead_mutex, philo->var->is_dead)))
	{
		pthread_mutex_lock(&philo->var->forks[philo->first_fork]);
		// if (philo->var->is_dead)
		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
		{
			pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
			break;
		}
		write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
		pthread_mutex_lock(&philo->var->forks[philo->second_fork]);
		// if (philo->var->is_dead)
		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
		{
			pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
			pthread_mutex_unlock(&philo->var->forks[philo->second_fork]);
			break;
		}
		write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
		write_status(EATING, philo, DEBUG_MODE);
		// philo->last_meal_timestamp = timestamp_in_ms();
		set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp, timestamp_in_ms());
		// usleep(philo->var->time_to_eat * 1000);
		usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000);
		pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->var->forks[philo->second_fork]);
		// if (philo->var->is_dead)
		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
			break;
		write_status(SLEEPING, philo, DEBUG_MODE);
		// usleep(philo->var->time_to_sleep * 1000);
		usleep(get_long(&philo->var->time2sleep_mutex, philo->var->time_to_sleep) * 1000);
		// if (philo->var->is_dead)
		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
			break;
		write_status(THINKING, philo, DEBUG_MODE);
		// philo->remaining_meals -= 1;
		set_int(&philo->remaining_meals_mutex, &philo->remaining_meals, philo->remaining_meals - 1);

		// count--;
	}
}
