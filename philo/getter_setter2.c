/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:18:22 by kkomasat          #+#    #+#             */
/*   Updated: 2025/07/17 15:18:23 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_long(pthread_mutex_t *mutex, long value)
{
    long ret;

    pthread_mutex_lock(mutex);
    ret = value;
    pthread_mutex_unlock(mutex);
    return (ret);
}

void set_long(pthread_mutex_t *mutex, long *dest, long value)
{
    pthread_mutex_lock(mutex);
    *dest = value;
    pthread_mutex_unlock(mutex);
}
