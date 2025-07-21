/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:18:04 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/17 15:43:41 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// time_t	get_timestamp(pthread_mutex_t *mutex, time_t value)
// {
// 	time_t	ret;

// 	pthread_mutex_lock(mutex);
// 	ret = value;
// 	pthread_mutex_unlock(mutex);
// 	return (ret);
// }

// void	set_timestamp(pthread_mutex_t *mutex, time_t *dest, time_t value)
// {
// 	pthread_mutex_lock(mutex);
// 	*dest = value;
// 	pthread_mutex_unlock(mutex);
// }

// int get_int(pthread_mutex_t *mutex, int value)
// int get_int(t_var *var, int code)
// {
// 	int ret;

// 	// pthread_mutex_lock(mutex);
// 	// ret = value;
// 	// pthread_mutex_unlock(mutex);
// 	// return (ret);
// 	// set_int(&var->allready_mutex, &var->all_threads_ready, 1);

// 	if (code == 0)
// 	{
// 		pthread_mutex_lock(&var->allready_mutex);
// 		ret = var->all_threads_ready;
// 		pthread_mutex_unlock(&var->allready_mutex);
// 	}
// 	// else if (code == 1)
// 	// {
// 	// 	pthread_mutex_lock(&var->isdead_mutex);
// 	// 	ret = var->is_dead;
// 	// 	pthread_mutex_unlock(&var->isdead_mutex);
// 	// }
// 	return (ret);
// }

// // void set_int(pthread_mutex_t *mutex, int *dest, int value)
// void set_int(t_var *var, int code, int value)
// {
// 	// pthread_mutex_lock(mutex);
// 	// *dest = value;
// 	// pthread_mutex_unlock(mutex);

// 	// set_int(&var->allready_mutex, &var->all_threads_ready, 1);
// 	if (code == 0)
// 	{
// 		pthread_mutex_lock(&var->allready_mutex);
// 		var->all_threads_ready = value;
// 		pthread_mutex_unlock(&var->allready_mutex);
// 	}
// }
