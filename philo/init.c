#include "philo.h"

void initialization(t_var *var)
{
	int i;

	i = 0;
	var->philo = malloc(sizeof(t_philo) * var->num_of_philo);
	while (i < var->num_of_philo)
	{
		var->philo[i].id = i + 1;
		var->philo[i].var = var;
		i++;
	}
}
