/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:35 by khkomasa          #+#    #+#             */
/*   Updated: 2025/02/24 12:30:08 by toon             ###   ########.fr       */
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

void write_status_debug ()
{

}

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long elapsed_time;

	elapsed_time = get_time_in_ms() - philo->var->start_time;
	if (debug)
		write_status_debug(status, philo, elapsed_time);
	else
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%.6ld %d has taken a fork\n", elapsed_time, philo->id);
		else if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%.6ld %d is eating\n", elapsed_time, philo->id);
	}
}
