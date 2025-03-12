#include "philo.h"

// static void eat(t_philo *philo)
// {
// 	// 1)
// 	safe_mutex_handle(&philo->first_fork->fork, LOCK);
// 	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
// 	safe_mutex_handle(&philo->first_fork->fork, LOCK);
// 	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

// 	// 2)
// 	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
// 	philo->meals_counter++;
// 	write_status(EATING, philo, DEBUG_MODE);
// 	precise_usleep(philo->table->time_to_eat, philo->table);
// 	if (philo->table->nbr_limit_meals > 0 && philo->meals_counter == philo->table->nbr_limit_meals)
// 		set_bool(&philo->philo_mutex, &philo->full, true);

// 	// 3)
// 	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
// 	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
// }

// void thinking(t_philo *philo, bool pre_simulation)
// {
// 	long t_eat;
// 	long t_sleep;
// 	long t_think;

// 	if (!pre_simulation)
// 		write_status(THINKING, philo, DEBUG_MODE);
// 	// if the system is even; we don't care, system already fair
// 	if (philo->table->philo_nbr % 2 == 0)
// 		return;
// 	// ODD, not ALWAYS fair
// 	t_eat = philo->table->time_to_eat;
// 	t_sleep = philo->table->time_to_sleep;
// 	t_think = t_eat * 2 - t_sleep;
// 	if (t_think < 0)
// 		t_think = 0;
// 	precise_usleep(t_think * 0.42, philo->table);
// }

void wait_all_threads(t_var *var)
{
	// printf("ID:%d, Status: %d\n", var->philo->id, var->all_threads_ready);
	while (!var->all_threads_ready)
		;
}

void lone_philo(t_philo *philo)
{
	wait_all_threads(philo->var);
	philo->last_meal_timestamp = timestamp_in_ms();
	pthread_mutex_lock(&philo->var->forks[philo->first_fork]);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (1)
	{
		if (timestamp_in_ms() - philo->last_meal_timestamp > philo->var->time_to_die)
		{
			philo->var->death_timestamp = timestamp_in_ms() - philo->var->start_timestamp;
			philo->var->dead_index = philo->id;
			philo->var->is_dead = 1;
			pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
			break;
		}
	}
}

void even_odd_approach(t_philo *philo)
{
	int count;

	wait_all_threads(philo->var);
	philo->last_meal_timestamp = timestamp_in_ms();
	if (philo->id % 2)
		usleep(philo->var->time_to_eat * 1000 * 0.5);
	if (philo->remaining_meals == -1)
		count = -1;
	else
		count = philo->remaining_meals;
	while (count && (!philo->var->is_dead))
	{
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
		philo->last_meal_timestamp = timestamp_in_ms();
		usleep(philo->var->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->var->forks[philo->first_fork]);
		pthread_mutex_unlock(&philo->var->forks[philo->second_fork]);
		if (philo->var->is_dead)
			break;
		write_status(SLEEPING, philo, DEBUG_MODE);
		usleep(philo->var->time_to_sleep * 1000);
		if (philo->var->is_dead)
			break;
		write_status(THINKING, philo, DEBUG_MODE);
		count--;
	}
}
