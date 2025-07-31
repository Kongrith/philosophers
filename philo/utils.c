/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:33:35 by khkomasa          #+#    #+#             */
/*   Updated: 2025/08/01 04:37:34 by kkomasat         ###   ########.fr       */
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
		usleep(50);
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

void	show_output(t_philo_status philo_status, \
t_philo *philo, long elapsed_time)
{
	if (!*philo->is_finish)
	{
		if (philo_status == TAKE_FIRST_FORK || philo_status == TAKE_SECOND_FORK)
			printf("%.3ld %d has taken a fork\n", elapsed_time, philo->id);
		else if (philo_status == EATING)
			printf("%.3ld %d is eating\n", elapsed_time, philo->id);
		else if (philo_status == SLEEPING)
			printf("%.3ld %d is sleeping\n", elapsed_time, philo->id);
		else if (philo_status == THINKING)
			printf("%.3ld %d is thinking\n", elapsed_time, philo->id);
	}
}

void	write_status(t_philo_status philo_status, t_philo *philo, bool debug)
{
	long	elapsed_time;

	if (debug)
		return ;
	if (philo_status == DIED || philo_status == FULL)
	{
		pthread_mutex_lock(philo->starttime_mutex);
		elapsed_time = current_time_msec() - philo->start_timestamp;
		if (philo_status == DIED)
			printf("%.3ld %d died\n", elapsed_time, philo->id);
		else
			printf("All philos has eaten the minimum meals\n");
		pthread_mutex_unlock(philo->starttime_mutex);
		return ;
	}
	pthread_mutex_lock(philo->starttime_mutex);
	elapsed_time = current_time_msec() - philo->start_timestamp;
	pthread_mutex_unlock(philo->starttime_mutex);
	pthread_mutex_lock(philo->finish_mutex);
	if (!*philo->is_finish)
		show_output(philo_status, philo, elapsed_time);
	pthread_mutex_unlock(philo->finish_mutex);
}
