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

time_t	get_timestamp(pthread_mutex_t *mutex, time_t value)
{
	time_t	ret;

	pthread_mutex_lock(mutex);
	ret = value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_timestamp(pthread_mutex_t *mutex, time_t *dest, time_t value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

int	get_int(pthread_mutex_t *mutex, int value)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_int(pthread_mutex_t *mutex, int *dest, int value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
