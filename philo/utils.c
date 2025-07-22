/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:35 by khkomasa          #+#    #+#             */
/*   Updated: 2025/07/21 22:54:01 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	current_time_msec(void)
{
	struct timeval	time;
	long			sec;
	long			usec;
	time_t			msec;

	gettimeofday(&time, NULL);
	sec = time.tv_sec;
	usec = time.tv_usec;
	msec = sec * 1000 + usec / 1000;
	return (msec);
}

int	precise_sleep(size_t milliseconds)
{
	size_t	start;

	start = current_time_msec();
	while ((current_time_msec() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	error_exit(int err_code, char *str)
{
	if (err_code == 0)
		printf("Error: '%s' shoud not be zero value\n", str);
	else if (err_code == -1)
		printf("Error: %s\n", str);
	else if (err_code == -2)
		printf("Error: '%s' shoud not be negative value\n", str);
	else if (err_code == -3)
		printf("Error: '%s' shoud be number\n", str);
	else if (err_code == -4)
		printf("Error: '%s' exceed MAX INTEGER\n", str);
	return (-1);
}

void	write_status(t_philo_status status, t_philo *philo, int id, bool debug)
{
	long	elapsed_time;

	pthread_mutex_lock(philo->starttime_mutex);
	elapsed_time = current_time_msec() - philo->start_timestamp;
	pthread_mutex_unlock(philo->starttime_mutex);
	if (!debug)
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%.3ld %d has taken a fork\n", elapsed_time, id);
		else if (status == EATING)
			printf("%.3ld %d is eating\n", elapsed_time, id);
		else if (status == SLEEPING)
			printf("%.3ld %d is sleeping\n", elapsed_time, id);
		else if (status == THINKING)
			printf("%.3ld %d is thinking\n", elapsed_time, id);
		else if (status == DIED)
			printf("%.3ld %d died\n", elapsed_time, id);
	}
}
