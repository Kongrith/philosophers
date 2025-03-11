#include "dining_philo.h"

/*
	0) wait all philos, synchro start
	1) endless loop philo
*/

void wait_all_threads(t_table *table)
{
	while(get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool ret;
	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		return (true);
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void increase_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

void de_synchronize_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
