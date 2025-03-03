#include "philo.h"

/*
void *lone_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}
*/
void lone_philo(t_philo *philo)
{
	// long elapsed_time;

	pthread_mutex_lock(&philo->var->forks[philo->first_fork]);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	// elapsed_time = get_time_in_ms() - philo->var->start_time;
	// printf("%.6ld %d has taken a fork\n", elapsed_time, philo->id);
	while (1)
	{
		if (get_time_in_ms() - philo->last_meal_time > philo->var->time_to_die)
		{
			philo->var->time_of_death = get_time_in_ms() - philo->var->start_time;
			philo->var->dead_index = philo->id;
			philo->var->is_dead = 1;
			pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
			break;
		}
	}
}

void even_odd_approach(t_philo *philo)
{
	// printf("must eat: %d\n", philo->must_eat);
	// usleep((philo->id*5)*1000*1000);
	while ((philo->must_eat) && (!philo->var->is_dead))
	{
		pthread_mutex_lock(&philo->var->forks[philo->first_fork]);
		write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
		pthread_mutex_lock(&philo->var->forks[philo->second_fork]);
		write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
		write_status(EATING, philo, DEBUG_MODE);
		usleep(philo->var->time_to_eat*1000);
		philo->last_meal_time = get_time_in_ms();
		pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->var->forks[philo->second_fork]);
		write_status(SLEEPING, philo, DEBUG_MODE);
		usleep(philo->var->time_to_sleep*1000);
		write_status(THINKING, philo, DEBUG_MODE);
		philo->must_eat--;
	}
	// printf("thread: %d is completed job !!\n", philo->id);
}
