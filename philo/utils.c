/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khkomasa <khkomasa@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:35 by khkomasa          #+#    #+#             */
/*   Updated: 2025/02/24 01:33:37 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t get_time_in_ms()
{
	struct timeval time;
	long sec;
	long usec;
	time_t msec;

	gettimeofday(&time, NULL); // get the current time
	sec = time.tv_sec;
	usec = time.tv_usec;
	msec = sec * 1000 + usec / 1000;
	return msec;
}

void error_exit(char *str)
{
	printf("%s\n", str);
}
