/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:19:42 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/17 16:04:39 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void lone_philo(t_philo *philo)
{
	wait_all_threads(philo->var);
	set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp,
				  timestamp_in_ms());
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (1)
	{
		if (timestamp_in_ms() - get_timestamp(&philo->lastmeal_mutex,
											  philo->last_meal_timestamp) >
			get_long(&philo->var->time2die_mutex,
					 philo->var->time_to_die))
		{
			break;
		}
	}
}

int stoping_criteria(t_philo *philo)
{
	if (get_int(&philo->remaining_meals_mutex, philo->remaining_meals) &&
		(!get_int(&philo->var->isdead_mutex, philo->var->is_dead)))
		return (1);
	else
		return (0);
}

void even_odd_approach(t_philo *philo)
{
	wait_all_threads(philo->var);
	set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp, timestamp_in_ms());
	start_scheme(philo);
	// if (get_int(&philo->id_mutex, philo->id) % 2 == 0)
	// 	usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000 * 0.5);
	// else if (get_int(&philo->id_mutex, philo->id) == philo->var->num_of_philo)
	// {
	// 	usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000 * 0.6);
	// }
	// while (get_int(&philo->remaining_meals_mutex, philo->remaining_meals) && (!get_int(&philo->var->isdead_mutex, philo->var->is_dead)))
	while (stoping_criteria(philo))
	{
		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
			break;
		if (eat_event(philo) < 0)
			break;
		// pthread_mutex_lock(&philo->var->forks[philo->first_fork]);
		// if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
		// {
		// 	pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
		// 	break;
		// }
		// write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
		// pthread_mutex_lock(&philo->var->forks[philo->second_fork]);
		// if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
		// {
		// 	pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
		// 	pthread_mutex_unlock(&philo->var->forks[philo->second_fork]);
		// 	break;
		// }
		// write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
		// write_status(EATING, philo, DEBUG_MODE);
		// set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp, timestamp_in_ms());
		// usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000);
		// pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
		// pthread_mutex_unlock(&philo->var->forks[philo->second_fork]);
		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
			break;
		if (sleep_event(philo) < 0)
			break;
		// write_status(SLEEPING, philo, DEBUG_MODE);
		// usleep(get_long(&philo->var->time2sleep_mutex, philo->var->time_to_sleep) * 1000);
		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
			break;
		if (think_event(philo) < 0)
			break;
		// write_status(THINKING, philo, DEBUG_MODE);
		set_int(&philo->remaining_meals_mutex, &philo->remaining_meals, philo->remaining_meals - 1);
	}
}
