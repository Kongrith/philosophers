#include "philo.h"

static void *routine(void *data)
{
	t_philo *philo;
	long msec;

	philo = (t_philo *)data;
	msec = get_time_in_ms() - philo->var->start_time;
	// printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, phil->pos, "has taken a fork");
	printf("%.6ld %d has taken a fork\n", msec, philo->id);
	return (0);
}

int start_simulation(t_var *var)
{
	int i;
	// pthread_t t1;

	i = 0;
	var->start_time = get_time_in_ms();
	while (i < var->num_of_philo)
	{
		// int *a = malloc(sizeof(int));
		// *a = i;
		if (pthread_create(&var->philo[i].thread, NULL, &routine, &var->philo[i]) != 0)
			perror("Failed to created thread");
		i++;
	}
	i = 0;
	while (i < var->num_of_philo)
	{
		if (pthread_join(var->philo[i].thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	return (0);
}
