/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:34:44 by kkomasat          #+#    #+#             */
/*   Updated: 2025/08/01 04:24:03 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stoping_criteria(t_philo *philo)
{
	pthread_mutex_lock(philo->finish_mutex);
	if (*philo->is_finish == 1)
	{
		pthread_mutex_unlock(philo->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->finish_mutex);
	return (0);
}
