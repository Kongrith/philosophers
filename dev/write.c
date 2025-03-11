#include "dining_philo.h"

/* 1.27.39
*/
static void write_status_debug(t_philo_status status, t_philo *philo, long elapse)
{
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !simulation_finished(philo->table))
		printf(W "%-6ld" RST " %d has taken a fork\n", elapse, philo->id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(W "%-6ld" C " %d is eating\n" RST, elapse, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(W "%-6ld" C " %d is sleeping\n" RST, elapse, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(W "%-6ld" C " %d is thinking\n" RST, elapse, philo->id);
	else if (status == DIED)
		printf(RED "%-6ld %d died\n" RST, elapse, philo->id);
}

/*	func to write philo status in a thread
	write
	philo's mutext ot read meal counter
	table's lock to read if end_simulation
*/
void write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long elapse;

	elapse = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return;

	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapse);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !simulation_finished(philo->table))
			printf(W "%-6ld" RST " %d has taken a fork\n", elapse, philo->id);
		else if (status == EATING  && !simulation_finished(philo->table))
			printf(W "%-6ld" C " %d is eating\n"RST, elapse, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			printf(W "%-6ld" C " %d is sleeping\n" RST, elapse, philo->id);
		else if (status == THINKING && !simulation_finished(philo->table))
			printf(W "%-6ld" C " %d is thinking\n" RST, elapse, philo->id);
		else if (status == DIED )
			printf(RED"%-6ld %d died\n"RST, elapse, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
