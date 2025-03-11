#include "dining_philo.h"

/*
*/
long gettime(t_time_code time_code)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec) / 1e6);
	else if (time_code == MILLISECOND)
		return ( (tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + (tv.tv_usec));
}

/*	Precise USLEEP

*/
void precise_usleep(long usec, t_table *table)
{
	long start;
	long elapseed;
	long rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		// 1)
		if (simulation_finished(table))
			break;
		elapseed = gettime(MICROSECOND) - start;
		rem = usec - elapseed;

		// to get a spinlock threshold
		if (rem > 1e3)
			usleep(rem / 2);
		else
			//Spin lock
			while (gettime(MICROSECOND) - start < usec)
				;
	}
}

void clean(t_table *table)
{
	t_philo *philo;
	int i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + 1;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

void error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

