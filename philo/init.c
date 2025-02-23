#include "philo.h"

static void init_mutexes(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		if (pthread_mutex_init(&var->forks[i], NULL))
			error_exit("Can not init mutext");
		i++;
	}
}

static void init_philos(t_var *var)
{
	int i;

	i = 0;
	while (i < var->num_of_philo)
	{
		var->philo[i].id = i + 1;
		var->philo[i].var = var;
		i++;
	}
}

void initialization(t_var *var)
{
	var->is_dead = 0;
	var->dead_index = 0;
	var->philo = malloc(sizeof(t_philo) * var->num_of_philo);
	var->forks = malloc(sizeof(pthread_mutex_t) * var->num_of_philo);
	init_philos(var);
	init_mutexes(var);
}
