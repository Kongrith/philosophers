#include "philo.h"

void wait_all_threads(t_var *var)
{
	// printf("ID:%d, Status: %d\n", var->philo->id, var->all_threads_ready);
	while (!var->all_threads_ready)
		;
}

void lone_philo(t_philo *philo)
{
	wait_all_threads(philo->var);
	philo->last_meal_time = timestamp_in_ms();
	pthread_mutex_lock(&philo->var->forks[philo->first_fork]);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (1)
	{
		if (timestamp_in_ms() - philo->last_meal_time > philo->var->time_to_die)
		{
			philo->var->time_of_death = timestamp_in_ms() - philo->var->start_time;
			philo->var->dead_index = philo->id;
			philo->var->is_dead = 1;
			pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
			break;
		}
	}
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

void even_odd_approach(t_philo *philo)
{
	int count;
	// int i;

	wait_all_threads(philo->var);
	philo->last_meal_time = timestamp_in_ms();
	if (philo->id % 2)
		usleep(200);
	if (philo->must_eat == -1)
		count = -1;
	else
		count = philo->must_eat;
	// i = 1;
	while (count && (!philo->var->is_dead))
	{
		// printf("ID:%d, Count:%d\n", philo->id, i);
		pthread_mutex_lock(&philo->var->forks[philo->first_fork]);
		if (philo->var->is_dead)
		{
			pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
			break;
		}
		write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
		pthread_mutex_lock(&philo->var->forks[philo->second_fork]);
		if (philo->var->is_dead)
		{
			pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
			pthread_mutex_unlock(&philo->var->forks[philo->second_fork]);
			break;
		}
		write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
		write_status(EATING, philo, DEBUG_MODE);
		philo->last_meal_time = timestamp_in_ms();
		// t_think = t_eat * 2 - t_sleep;
		// if (t_think < 0)
		// 	t_think = 0;
		usleep(philo->var->time_to_eat * 1000);
		// precise_usleep(philo->var->time_to_eat * 1000, philo);

		pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->var->forks[philo->second_fork]);
		if (philo->var->is_dead)
			break;
		write_status(SLEEPING, philo, DEBUG_MODE);
		usleep(philo->var->time_to_sleep * 1000);
		// precise_usleep(philo->var->time_to_sleep * 1000, philo);
		if (philo->var->is_dead)
			break;
		write_status(THINKING, philo, DEBUG_MODE);
		count--;
		//  philo->must_eat--;
		// i++;
	}
}
