/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 02:42:45 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/20 02:42:47 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int chk_full(t_philo *philos)
{
    int i;
    int full_philo;

    i = 0;
    full_philo = 0;
    if (philos[0].required_meals == -1)
        return (0);
    while (i < philos[0].num_of_philo)
    {
        pthread_mutex_lock(philos[i].lastmeal_mutex);
        if (philos[i].meals_eaten >= philos[i].required_meals)
            full_philo++;
        pthread_mutex_unlock(philos[i].lastmeal_mutex);
        i++;
    }
    if (full_philo >= philos[0].num_of_philo)
    {
        printf("All philos has eaten the minimum meals\n");
        pthread_mutex_lock(philos[0].dead_mutex);
        *philos->is_dead = 1;
        pthread_mutex_unlock(philos[0].dead_mutex);
        return (1);
    }
    return (0);
}

int death_criteria(t_philo *philo)
{
    int time_to_die;
    long lastmeal_timestamp;

    time_to_die = philo->time_to_die;
    pthread_mutex_lock(philo->lastmeal_mutex);
    lastmeal_timestamp = current_time_msec() - philo->lastmeal_timestamp;
    pthread_mutex_unlock(philo->lastmeal_mutex);
    if (lastmeal_timestamp >= time_to_die && philo->is_eating == 0)
        return (1);
    else
        return (0);
}

int chk_dead(t_philo *philos)
{
    int i;
    int num_philo;

    i = 0;
    num_philo = philos[0].num_of_philo;
    while (i < num_philo)
    {
        if (death_criteria(&philos[i]))
        {
            pthread_mutex_lock(philos[i].dead_mutex);
            *philos->is_dead = 1;
            write_status(DIED, &philos[i], i + 1, DEBUG_MODE);
            pthread_mutex_unlock(philos[i].dead_mutex);
            return (1);
        }
        i++;
    }
    return (0);
}

void *monitor_routine(void *data)
{
    t_philo *philos;

    philos = (t_philo *)data;
    while (!chk_dead(philos) && !chk_full(philos))
        ;
    // {
    //     // if (chk_dead(philos) || chk_full(philos))
    //     //     break;
    // }
    return (NULL);
}