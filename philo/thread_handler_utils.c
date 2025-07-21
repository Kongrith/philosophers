/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:34:44 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/17 17:25:23 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	start_scheme(t_philo *philo)
// {
// 	if (get_int(&philo->id_mutex, philo->id) % 2 == 0)
// 		usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000 * 0.5);
// 	else if (get_int(&philo->id_mutex, philo->id) == philo->var->num_of_philo)
// 		usleep(get_long(&philo->var->time2eat_mutex, philo->var->time_to_eat) * 1000 * 0.6);
// }

// void wait_all_threads(t_var *var)
void wait_all_threads(t_philo *philo)
{
    // int ready;
    (void)philo;
    // ready = 0;
    // while (!get_int(&var->allready_mutex, var->all_threads_ready))
    // while (!get_int(philo->ready_mutex, 0))
    //     ;

    // while (!ready)
    // {
    //     pthread_mutex_lock(philo->ready_mutex);
    //     ready = philo->var->all_threads_ready;
    //     pthread_mutex_unlock(philo->ready_mutex);
    // }
}

int eat_event(t_philo *philo)
{
    pthread_mutex_lock(&philo->forks[philo->first_fork]);
    if (stoping_criteria(philo) || philo->num_of_philo == 1)
    {
        if (philo->num_of_philo == 1)
            precise_sleep(philo->time_to_die);
        pthread_mutex_unlock(&philo->forks[philo->first_fork]);
        return (-1);
    }
    write_status(TAKE_FIRST_FORK, philo, philo->id, DEBUG_MODE);
    pthread_mutex_lock(&philo->forks[philo->second_fork]);
    philo->is_eating = 1;
    if (stoping_criteria(philo))
    {
        pthread_mutex_unlock(&philo->forks[philo->first_fork]);
        pthread_mutex_unlock(&philo->forks[philo->second_fork]);
        return (-1);
    }
    write_status(TAKE_SECOND_FORK, philo, philo->id, DEBUG_MODE);
    write_status(EATING, philo, philo->id, DEBUG_MODE);
    pthread_mutex_lock(philo->lastmeal_mutex);
    philo->lastmeal_timestamp = current_time_msec();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->lastmeal_mutex);
    precise_sleep(philo->time_to_eat);
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->forks[philo->first_fork]);
    pthread_mutex_unlock(&philo->forks[philo->second_fork]);
    if (stoping_criteria(philo))
        return (-1);
    return (0);
}

int sleep_event(t_philo *philo)
{
    write_status(SLEEPING, philo, philo->id, DEBUG_MODE);
    // usleep(philo->time_to_sleep * 1000);
    precise_sleep(philo->time_to_sleep);
    if (stoping_criteria(philo))
        return (-1);
    return (0);
}

int think_event(t_philo *philo)
{
    write_status(THINKING, philo, philo->id, DEBUG_MODE);
    // precise_sleep(philo->time_to);
    if (stoping_criteria(philo))
        return (-1);
    return (0);
}
