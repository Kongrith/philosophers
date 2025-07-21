/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:18 by khkomasa          #+#    #+#             */
/*   Updated: 2025/07/17 16:02:27 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void print_message(t_philo *philo, int id)
// {
//     size_t time;

//     pthread_mutex_lock(philo->starttime_mutex);
//     time = current_time_msec() - philo->start_timestamp;
//     printf("%.3ld %d has taken a fork\n", time, id);
//     pthread_mutex_unlock(philo->starttime_mutex);
// }

int stoping_criteria(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_mutex);
    if (*philo->is_dead == 1)
    {
        pthread_mutex_unlock(philo->dead_mutex);
        return (1);
    }
    pthread_mutex_unlock(philo->dead_mutex);
    return (0);
}

static void *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    if (philo->id % 2 == 0)
        // usleep(philo->time_to_eat * 1000 * 0.5);
        precise_sleep(philo->time_to_eat * 0.5);
    // precise_sleep(1);
    else if (philo->id == philo->num_of_philo)
        // usleep(philo->time_to_eat * 1000 * 0.6);
        precise_sleep(philo->time_to_eat * 0.6);
    while (!stoping_criteria(philo))
    {
        // if (stoping_criteria(philo))
        //     break;
        if (eat_event(philo) < 0)
            break;
        // if (stoping_criteria(philo))
        //     break;
        // sleep_event(philo);
        // sleep_event(philo);
        if (sleep_event(philo) < 0)
            break;
        // if (stoping_criteria(philo))
        //     break;
        // think_event(philo);
        if (think_event(philo) < 0)
            break;
        // if (stoping_criteria(philo))
        //     break;
    }
    // if (philo->num_of_philo == 1)
    // {
    //     write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    //     usleep(philo->time_to_die * 1000);
    // }
    // else
    // {
    //     while (!stoping_criteria(philo))
    //     {
    //         eat_event(philo);
    //         sleep_event(philo);
    //         think_event(philo);
    //     }
    // }
    return (NULL);
}

void create_threads(t_var *var)
{
    int i;
    pthread_t monitor;

    i = 0;
    if (pthread_create(&monitor, NULL, &monitor_routine, var->philos) != 0)
        error_exit(-1, "Failed to created thread");
    while (i < var->num_of_philo)
    {
        if (pthread_create(&var->philos[i].thread, NULL, &philo_routine, &var->philos[i]) != 0)
            error_exit(-1, "Failed to created thread");
        i++;
    }
    // if (pthread_create(&var->monitor->thread, NULL, &monitor_routine, var) != 0)
    i = 0;
    if (pthread_join(monitor, NULL) != 0)
        error_exit(-1, "Failed to join thread");
    while (i < var->num_of_philo)
    {
        if (pthread_join(var->philos[i].thread, NULL) != 0)
            error_exit(-1, "Failed to join thread");
        i++;
    }
    // printf("joined\n");
}

// void join_threads(t_var *var)
// {
//     int i;

//     i = 0;
//     while (i < var->num_of_philo)
//     {
//         if (pthread_join(var->philo[i].thread, NULL) != 0)
//             error_exit(-1, "Failed to join thread");
//         i++;
//     }
//     if (pthread_join(var->monitor->thread, NULL) != 0)
//         error_exit(-1, "Failed to join thread");
// }

int start_simulation(t_var *var)
{
    // create_threads(var);
    // 	set_timestamp(&var->starttime_mutex, &var->start_timestamp, timestamp_in_ms());
    // 	set_int(&var->allready_mutex, &var->all_threads_ready, 1);
    // set_int(var, 0, 1);

    (void)var;
    // join_threads(var);
    // pthread_mutex_lock(&var->allready_mutex);
    // var->all_threads_ready = 1;
    // pthread_mutex_unlock(&var->allready_mutex);
    // 	if (get_int(&var->isdead_mutex, var->is_dead))
    // 		write_status(DIED, var->philo, DEBUG_MODE);
    printf("completed !!\n");
    return (0);
}
