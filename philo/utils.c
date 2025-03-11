/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:35 by khkomasa          #+#    #+#             */
/*   Updated: 2025/03/06 14:32:17 by toon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t timestamp_in_ms()
{
	struct timeval time;
	long sec;
	long usec;
	time_t msec;

	gettimeofday(&time, NULL);
	sec = time.tv_sec;
	usec = time.tv_usec;
	msec = sec * 1000 + usec / 1000;
	return msec;
}

void precise_usleep(long usec, t_philo *philo)
{
	long start;
	long elapseed;
	long rem;

	start = timestamp_in_ms();
	while (timestamp_in_ms() - start < usec)
	{
		// 1)
		if (philo->var->is_dead)
			break;
		elapseed = timestamp_in_ms() - start;
		rem = usec - elapseed;

		// to get a spinlock thresholda
		if (rem > 1e3)
			usleep(rem / 2);
		else
			// Spin lock
			while (timestamp_in_ms() - start < usec)
				;
	}
}


void error_exit(char *str)
{
	printf("%s\n", str);
}

// void write_status_debug ()
// {

// }

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long elapsed_time;

	elapsed_time = timestamp_in_ms() - philo->var->start_time;
	if (debug)
	{
		// write_status_debug(status, philo, elapsed_time);
	}
	else
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%.3ld %d has taken a fork\n", elapsed_time, philo->id);
		else if (status == EATING)
			printf("%.3ld %d is eating\n", elapsed_time, philo->id);
		else if (status == SLEEPING)
			printf("%.3ld %d is sleeping\n", elapsed_time, philo->id);
		else if (status == THINKING)
			printf("%.3ld %d is thinking\n", elapsed_time, philo->id);
	}
}
