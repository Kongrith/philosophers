/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:34:44 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/17 16:34:45 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_scheme(t_philo *philo)
{
    if (get_int(&philo->id_mutex, philo->id) % 2 == 0)
        usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000 * 0.5);
    else if (get_int(&philo->id_mutex, philo->id) == philo->var->num_of_philo)
        usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000 * 0.6);
}

void wait_all_threads(t_var *var)
{
    while (!get_int(&var->allready_mutex, var->all_threads_ready))
        ;
}

int eat_event(t_philo *philo)
{
    pthread_mutex_lock(&philo->var->forks[philo->first_fork]);
    if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
    {
        pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
        return (-1);
    }
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    pthread_mutex_lock(&philo->var->forks[philo->second_fork]);
    if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
    {
        pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
        pthread_mutex_unlock(&philo->var->forks[philo->second_fork]);
        return (-1);
    }
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
    write_status(EATING, philo, DEBUG_MODE);
    set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp, timestamp_in_ms());
    usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000);
    pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
    pthread_mutex_unlock(&philo->var->forks[philo->second_fork]);
    return (0);
}

int sleep_event(t_philo *philo)
{
    write_status(SLEEPING, philo, DEBUG_MODE);
    usleep(get_long(&philo->var->time2sleep_mutex, philo->var->time_to_sleep) * 1000);
    return (0);
}

int think_event(t_philo *philo)
{
    write_status(THINKING, philo, DEBUG_MODE);
    return (0);
}