#include "philo.h"

/*			t_die
	last_meal--------------last_meal
*/
// static bool philo_died(t_philo *philo)
// {
// 	long	elapsed;
// 	long	t_to_die;

// 	if (get_bool(&philo->philo_mutex, &philo->full))
// 		return (false);

// 	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
// 	t_to_die = philo->table->time_to_die / 1000;

// 	if (elapsed > t_to_die)
// 		return (true);
// 	return (false);
// }

// void *monitor_dinner(void *data)
// {
// 	int i;
// 	t_table *table;
// 	table = (t_table *)data;

// 	// make sure all philo running
// 	// spinlock till all threads run
// 	while(!all_threads_running(&table->table_mutex, &table->threads_running_nbr, table->philo_nbr))
// 		;

// 	while (!simulation_finished(table))
// 	{
// 		i = -1;
// 		while (++i < table->philo_nbr && !simulation_finished(table))
// 		{
// 			if (philo_died(table->philos + i))
// 			{
// 				set_bool(&table->table_mutex, &table->end_simulation, true);
// 				write_status(DIED, table->philos + i, DEBUG_MODE);
// 			}
// 		}
// 	}
// 	return (NULL);
// }

void *monitor(void *data)
{
	int i;
	t_var *var;

	var = (t_var *)data;
	time_t spent_time;
	wait_all_threads(var);
	usleep(var->time_to_die * 1000 * 0.5);
	while (!var->is_dead)
	{
		i = 0;
		while ((i < var->num_of_philo) && (!var->is_dead))
		{
			spent_time = timestamp_in_ms() - var->philo->last_meal_time;
			if (spent_time >= var->time_to_die)
			{
				var->time_of_death = timestamp_in_ms() - var->start_time;
				var->dead_index = i + 1;
				var->is_dead = 1;
			}
			i++;
		}
	}
	return (NULL);
}
