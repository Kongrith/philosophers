#include "dining_philo.h"

void thinking(t_philo *philo, bool pre_simulation)
{
	long t_eat;
	long t_sleep;
	long t_think;

	if (!pre_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	// if the system is even; we don't care, system already fair
	if (philo->table->philo_nbr % 2 == 0)
		return;
	// ODD, not ALWAYS fair
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

/*
*/
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

/*	EAT routine
	1) grab the forks: here first & second is handy. I DONT worry about left or right
	2) eat: write eat, update last meal, update meal counter. Eventually, full (bool).
	3) release the fork
*/
static void eat(t_philo *philo)
{
	// 1)
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

	// 2)
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0 && philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);

	// 3)
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/*
	0) wait all philos, synchro start
	1) endless loop philo
*/
void *dinner_simulation(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;

	// spin lock
	wait_all_threads(philo->table);

	// syncho with monitor
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);

	// set last meal time
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));

	// de-synchronoization
	de_synchronize_philos(philo);

	while (!simulation_finished(philo->table))
	{
		// 1) am i full ?
		if (philo->full)
			break;

		// 2) eat
		eat(philo);

		// 3) sleep -> write_status & precise usleep
		write_status(SLEEPING, philo, 0);
		precise_usleep(philo->table->time_to_sleep, philo->table);

		// 4) thinking
		thinking(philo, false);
	}

	return (NULL);
}

/*
	./philo 5 800 200 200 [5]
	0) If no meals, return -> [0]
		0.1) If only one philo -> ad hoc function
	1) Create all threads, all philos
	2) Create a monitor thread
	3) Synchronize the beginning of the simulation
		pthread_create -> philo start running !
		every philo start simultaneously
	4) Join everyone
*/
void dinner_start(t_table *table)
{
	int i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return; // back to main, clean
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
	}
	// monitor
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);

	// start simulation
	table->start_simulation = gettime(MILLISECOND);

	// now all threads are ready!
	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	// wait for everyone
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);

	// If we manage to reach this line all philos are FULL !!
	set_bool(&table->table_mutex, &table->end_simulation, true);

	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
