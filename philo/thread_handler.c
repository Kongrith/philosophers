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

// static void aaa(t_philo *philo, t_philo_status status, bool debug)
// {
//     long elapsed_time;
//     elapsed_time = current_time_msec() - philo->start_timestamp;
//     printf("%.3ld %d has taken a fork %d %d\n ", elapsed_time, philo->id, status, debug);
// }

// void lone_philo(t_philo *philo)
// {
// while (!stoping_criteria(philo))
// {
//     //     printf("loop\n");
//     eat_event(philo);
//     //     sleep_event(philo);
//     //     think_event(philo);
// }
// write_status(TAKE_FIRST_FORK, philo, 0);
// printf(":)");
// long elapsed_time;

// elapsed_time = current_time_msec() - philo->start_timestamp;
// printf("%.3ld %d died\n", elapsed_time, 1);
// write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
// aaa(philo, TAKE_FIRST_FORK, false);
// write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
// long elapsed_time;

// pthread_mutex_lock(philo->starttime_mutex);
// elapsed_time = current_time_msec() - philo->start_timestamp;
// printf("%.3ld %d has taken a fork\n", elapsed_time, 0);
// pthread_mutex_unlock(philo->starttime_mutex);
//     print_message(philo, 1);
//     while (1)
//     {
//         if (stoping_criteria(philo))
//             break;
//     }
// }

// void lone_philo(t_philo *philo)
// {
//     (void)philo;
//     // 	set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp, timestamp_in_ms());
//     // 	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
//     // 	while (1)
//     // 	{
//     // 		if (timestamp_in_ms() - get_timestamp(&philo->lastmeal_mutex, philo->last_meal_timestamp) > get_long(&philo->var->time2die_mutex, philo->var->time_to_die))
//     // 		{
//     // 			break ;
//     // 		}
//     // 	}
//     // (void)philo;

//     printf("philo completed\n");
// }

// int	stoping_criteria(t_philo *philo)
// {
// 	if (get_int(&philo->remaining_meals_mutex, philo->remaining_meals) && (!get_int(&philo->var->isdead_mutex, philo->var->is_dead)))
// 		return (1);
// 	else
// 		return (0);
// }

// void even_odd_approach(t_philo *philo)
// {
//     while (!stoping_criteria(philo))
//     {
//         //     printf("loop\n");
//         eat_event(philo);
//         //     sleep_event(philo);
//         //     think_event(philo);
//     }
//     // wait_all_threads(philo->var);
//     // wait_all_threads(philo);

//     // 	set_timestamp(&philo->lastmeal_mutex, &philo->last_meal_timestamp,  timestamp_in_ms());
//     // 	start_scheme(philo);
//     // 	while (stoping_criteria(philo))
//     // 	{
//     // 		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
//     // 			break ;
//     // 		if (eat_event(philo) < 0)
//     // 			break ;
//     // 		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
//     // 			break ;
//     // 		if (sleep_event(philo) < 0)
//     // 			break ;
//     // 		if (get_int(&philo->var->isdead_mutex, philo->var->is_dead))
//     // 			break ;
//     // 		if (think_event(philo) < 0)
//     // 			break ;
//     // 		set_int(&philo->remaining_meals_mutex, &philo->remaining_meals, philo->remaining_meals - 1);
//     // 	}
// }
