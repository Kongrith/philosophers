/*
ref: https://www.youtube.com/watch?v=UGQsvVKwe90
ref: https://github.com/Jamshidbek2000/philosophers_42

Race Conditions

Problem:
1) Deadlock: In the Dining Philosophers problem, a deadlock can happen if all 5 philosophers
	pick up 1 fork either only their left or only on their right.
2) Starvation:  If a philo is not able to eat for a period of time,
	philo may die from starvation.

Possible Solution (ref: https://www.youtube.com/watch?v=Dt51GebwNR0)
1) Resource Hierarchy Solution: ref: https://github.com/jtran270/dining-philosophers
2) Arbitrator solution
3) Chandy/Misra solution

Coffman conditions (ref: https://www.cs.yale.edu/homes/aspnes/pinewiki/Deadlock.html):
No mutual exclusion
No hold-and-wait
Allow preemption
Eliminate cycles
*/

#ifndef DINING_PHILO_H
# define DINING_PHILO_H

# include <stdio.h>		// printf
# include <stdlib.h> 	// malloc, free
# include <unistd.h>		// write, usleep
# include <stdbool.h>
# include <pthread.h>	// mutex: init destroy lock unlock, threadL create join detach
# include <sys/time.h>	// gettimeofday
# include <limits.h>		// INT_MAX
# include <errno.h>
# include <stddef.h>
/*
ANSI Escape Sequence for Bold Text Colors
printf(R "this is a read text.", RST);
printf(B "this is a read text.", RST);
*/
# define RST	"\033[0m"			// reset to default color
# define RED "\033[1;31m"		// Bold Red
# define G "\033[1;32m"			// Bold Green
# define Y "\033[1;33m"			// Bold Yellow
# define B "\033[1;34m"			// Bold Blue
# define M "\033[1;35m"			// Bold Magenta
# define C "\033[1;36m"			// Bold Cyan
# define W "\033[1;37m"			// Bold White

#define DEBUG_MODE false
typedef enum
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
} t_philo_status;

typedef enum
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
} t_time_code;

typedef enum {
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
} t_opcode;

typedef pthread_mutex_t t_mtx;	// code more readable
typedef struct s_table t_table;	// IOT for compiler
// typedef struct s_fork t_fork;	// IOT for compiler

// Fork: Array of Mutex
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
} t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time; 	// time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;			// philo is a thread
	t_mtx		philo_mutex;
	t_table		*table;
} t_philo;

/*
*/
struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;		// [5] | Flag if -1
	long 		start_simulation;
	bool		end_simulation; // Philo dies or all philos full
	bool		all_threads_ready;
	long		threads_running_nbr;
	pthread_t monitor;
	t_mtx 		table_mutex; // avoid race condition
	t_mtx 		write_mutex;
	t_fork 		*forks;
	t_philo 	*philos;
};

void error_exit(const char *error);
void parse_input(t_table *table, char **av);
void safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
void *safe_malloc(size_t bytes);
void data_init(t_table *table);
void dinner_start(t_table *table);

void set_bool(t_mtx *mutex, bool *dest, bool value);
bool get_bool(t_mtx *mutex, bool *value);
void set_long(t_mtx *mutex, long *dest, bool value);
long get_long(t_mtx *mutex, long *value);
bool simulation_finished(t_table *table);
void wait_all_threads(t_table *table);
long gettime(t_time_code time_code);
void precise_usleep(long usec, t_table *table);
void write_status(t_philo_status status, t_philo *philo, bool debug);
void *monitor_dinner(void *data);
bool all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void increase_long(t_mtx *mutex, long *value);
void clean(t_table *table);
void thinking(t_philo *philo, bool pre_simulation);
void de_synchronize_philos(t_philo *philo);
#endif
