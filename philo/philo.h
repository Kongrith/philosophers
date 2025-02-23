#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>	// printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <stdbool.h>
# include <pthread.h> // mutex: init destroy lock unlock, threadL create join detach
# include <sys/time.h> // gettimeofday
# include <limits.h>	  // INT_MAX
# include <pthread.h>

typedef struct s_var t_var;
typedef struct s_philo
{
	int id;
	t_var *var;
	pthread_t thread;
} t_philo;

typedef struct s_var
{
	int num_of_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int limit_meals;
	int is_dead;
	int dead_index;
	time_t start_time;
	t_philo *philo;
	pthread_mutex_t *forks;
} t_var;


// init.c
void initialization(t_var *var);

// parse input
void parse_input(t_var *var, int argc, char *argv[]);

// sim.c
int start_simulation(t_var *var);

// utils.c
void error_exit(char *str);
time_t get_time_in_ms();

#endif
