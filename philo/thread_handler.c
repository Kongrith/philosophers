/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 21:53:19 by kkomasat          #+#    #+#             */
/*   Updated: 2025/08/01 15:30:02 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	extend_eat_event(t_philo *philo)
{
	pthread_mutex_lock(philo->second_fork);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	write_status(EATING, philo, DEBUG_MODE);
	pthread_mutex_lock(philo->eating_mutex);
	philo->is_eating = 1;
	pthread_mutex_unlock(philo->eating_mutex);
	pthread_mutex_lock(philo->lastmeal_mutex);
	philo->lastmeal_timestamp = current_time_msec();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->lastmeal_mutex);
	precise_sleep(philo->time_to_eat);
	pthread_mutex_lock(philo->eating_mutex);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->eating_mutex);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

static int	eat_event(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	if (stoping_criteria(philo) || philo->num_of_philo == 1)
	{
		if (philo->num_of_philo == 1)
			precise_sleep(philo->time_to_die);
		pthread_mutex_unlock(philo->first_fork);
		return (-1);
	}
	extend_eat_event(philo);
	if (stoping_criteria(philo))
		return (-1);
	return (0);
}

static int	sleep_event(t_philo *philo)
{
	pthread_mutex_lock(philo->finish_mutex);
	if (*philo->is_finish)
	{
		pthread_mutex_unlock(philo->finish_mutex);
		return (-1);
	}
	pthread_mutex_unlock(philo->finish_mutex);
	write_status(SLEEPING, philo, DEBUG_MODE);
	precise_sleep(philo->time_to_sleep);
	return (0);
}

static int	think_event(t_philo *philo)
{
	long	value;

	pthread_mutex_lock(philo->finish_mutex);
	if (*philo->is_finish)
	{
		pthread_mutex_unlock(philo->finish_mutex);
		return (-1);
	}
	pthread_mutex_unlock(philo->finish_mutex);
	write_status(THINKING, philo, DEBUG_MODE);
	if (philo->num_of_philo % 2 == 0)
	{
		value = philo->time_to_eat - philo->time_to_sleep - 10;
		if (value > 0)
			precise_sleep(value);
	}
	else
	{
		value = (2 * philo->time_to_eat) - philo->time_to_sleep - 10;
		if (value > 0)
			precise_sleep(value);
	}
	return (0);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		precise_sleep(5);
	else if (philo->id == philo->num_of_philo && philo->num_of_philo != 1)
		precise_sleep(10);
	while (!stoping_criteria(philo))
	{
		if (eat_event(philo) < 0)
			break ;
		if (sleep_event(philo) < 0)
			break ;
		if (think_event(philo) < 0)
			break ;
	}
	return (NULL);
}
