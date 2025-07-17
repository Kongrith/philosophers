/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:19:42 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/17 17:28:05 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lone_philo(t_philo *philo)
{
	wait_all_threads(philo->var);
	set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp, \
timestamp_in_ms());
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (1)
	{
		if (timestamp_in_ms() - get_timestamp(&philo->lastmeal_mutex, \
philo->last_meal_timestamp) > get_long(&philo->var->time2die_mutex, \
philo->var->time_to_die))
		{
			break ;
		}
	}
}

int	stoping_criteria(t_philo *philo)
{
	if (get_int(&philo->remaining_meals_mutex, philo->remaining_meals) && \
(!get_int(&philo->var->isdead_mutex, philo->var->is_dead)))
		return (1);
	else
		return (0);
}

void	even_odd_approach(t_philo *philo)
{
	wait_all_threads(philo->var);
	set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp, \
timestamp_in_ms());
	start_scheme(philo);
	while (stoping_criteria(philo))
	{
		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
			break ;
		if (eat_event(philo) < 0)
			break ;
		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
			break ;
		if (sleep_event(philo) < 0)
			break ;
		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
			break ;
		if (think_event(philo) < 0)
			break ;
		set_int(&philo->remaining_meals_mutex, &philo->remaining_meals, \
philo->remaining_meals - 1);
	}
}
