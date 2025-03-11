
#include <stdio.h>	// printf
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, usleep
#include <stdbool.h>
#include <pthread.h> // mutex: init destroy lock unlock, threadL create join detach

#include <sys/time.h> // gettimeofday
#include <limits.h>	  // INT_MAX
#include <pthread.h>

/*
number_of_philosophers
time_to_die
time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]

cc philo.c
./a.out 1 b c d
*/

typedef struct s_var t_var;
typedef struct s_phil
{
	int			id;
	t_var		*var;
	pthread_t	thread;
} t_phil;

typedef struct s_var
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	time_t	start_time;
	t_phil	*phil;
} t_var;

time_t get_time_in_ms()
{
	struct timeval time;
	long sec;
	long usec;
	time_t msec;

	gettimeofday(&time, NULL); // get the current time
	sec = time.tv_sec;
	usec = time.tv_usec;
	msec = sec * 1000 + usec / 1000;
	return msec;
}

void *routine(void *data)
{
	t_phil	*phil;
	long	msec;

	phil = (t_phil *)data;
	msec = get_time_in_ms() - phil->var->start_time;
	// printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, phil->pos, "has taken a fork");
	printf("%.6ld %d has taken a fork\n", msec, phil->id);
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
		if (pthread_create(&var->phil[i].thread, NULL, &routine, &var->phil[i]) != 0)
			perror("Failed to created thread");
		i++;
	}
	i = 0;
	while (i < var->num_of_philo)
	{
		if (pthread_join(var->phil[i].thread, NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
}

void initialization(t_var *var, char *argv[])
{
	int i;

	i = 0;
	var->num_of_philo = atoi(argv[1]);
	var->phil = malloc(sizeof(t_phil) * var->num_of_philo);

	while (i < var->num_of_philo)
	{
		var->phil[i].id = i;
		var->phil[i].var = var;
		i++;
	}
}

/*
cc -pthread philo.c
./a.out 1 b c d
*/
int main(int argc, char *argv[])
{
	t_var var;

	if (argc == 5)
	{

		initialization(&var, argv);
		start_simulation(&var);
		// printf("start_time: %ld\n", var.start_time);
	}

	return (0);
}
