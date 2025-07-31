/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:35 by khkomasa          #+#    #+#             */
/*   Updated: 2025/07/26 03:11:45 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t current_time_msec(void)
{
	struct timeval time;
	long sec;
	long usec;
	time_t msec;

	gettimeofday(&time, NULL);
	sec = time.tv_sec;
	usec = time.tv_usec;
	msec = sec * 1000 + usec / 1000;
	return (msec);
}

int precise_sleep(size_t milliseconds)
{
	size_t start;

	start = current_time_msec();
	while ((current_time_msec() - start) < milliseconds)
		usleep(50);
	return (0);
}

int error_exit(int err_code, char *str)
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

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long elapsed_time;
	int dead_status;

	if (debug)
		return;

	// pthread_mutex_lock(philo->starttime_mutex);
	// elapsed_time = current_time_msec() - philo->start_timestamp;
	// pthread_mutex_unlock(philo->starttime_mutex);
	// if (!debug)
	// {
	// 	if (status == DIED)
	// 		printf("%.3ld %d died\n", elapsed_time, philo->id);
	// }

	pthread_mutex_lock(philo->dead_mutex);
	dead_status = *philo->is_dead;
	if (dead_status)
	{
		if (status == DIED)
		{
			pthread_mutex_lock(philo->starttime_mutex);
			elapsed_time = current_time_msec() - philo->start_timestamp;
			printf("%.3ld %d died\n", elapsed_time, philo->id);
			pthread_mutex_unlock(philo->starttime_mutex);
		}
		pthread_mutex_unlock(philo->dead_mutex);
		return;
	}
	pthread_mutex_lock(philo->starttime_mutex);
	elapsed_time = current_time_msec() - philo->start_timestamp;
	pthread_mutex_unlock(philo->starttime_mutex);
	if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		printf("%.3ld %d has taken a fork\n", elapsed_time, philo->id);
	else if (status == EATING)
		printf("%.3ld %d is eating\n", elapsed_time, philo->id);
	else if (status == SLEEPING)
		printf("%.3ld %d is sleeping\n", elapsed_time, philo->id);
	else if (status == THINKING)
		printf("%.3ld %d is thinking\n", elapsed_time, philo->id);
	pthread_mutex_unlock(philo->dead_mutex);
	// if (!debug && !dead_status)
	// // if (!debug)
	// {
	// 	if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
	// 		printf("%.3ld %d has taken a fork\n", elapsed_time, philo->id);
	// 	else if (status == EATING)
	// 		printf("%.3ld %d is eating\n", elapsed_time, philo->id);
	// 	else if (status == SLEEPING)
	// 		printf("%.3ld %d is sleeping\n", elapsed_time, philo->id);
	// 	else if (status == THINKING)
	// 		printf("%.3ld %d is thinking\n", elapsed_time, philo->id);
	// }
	// else if (dead_status)
	// {
	// 	if (status == DIED)
	// 		printf("%.3ld %d died\n", elapsed_time, philo->id);
	// 	// else if (status == FULL)
	// 	// 	printf("All philos has eaten the minimum meals\n");
	// 	// else
	// 	// 	printf("All philos has eaten the minimum meals\n");
	// }
}
