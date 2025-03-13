
#include "philo.h"

// var->philo = malloc(sizeof(t_philo) * var->num_of_philo);
// 	var->monitor = malloc(sizeof(t_monitor));
// 	var->forks = malloc(sizeof(pthread_mutex_t) * var->num_of_philo);

/*
typedef struct s_fork
{
    t_mtx fork;
    int fork_id;
} t_fork;

typedef struct s_philo
{
    int id;
    long meals_counter;
    bool full;
    long last_meal_timestamp; // time passed from last meal
    t_fork *first_fork;
    t_fork *second_fork;
    pthread_t thread_id; // philo is a thread
    t_mtx philo_mutex;
    t_table *table;
} t_philo;
*/
// void clean(t_table *table)
// {
// 	t_philo *philo;
// 	int i;

// 	i = -1;
// 	while (++i < table->philo_nbr)
// 	{
// 		philo = table->philos + 1;
// 		safe_mutex_handle(&philo->philo_mutex, DESTROY);
// 	}
// 	safe_mutex_handle(&table->write_mutex, DESTROY);
// 	safe_mutex_handle(&table->table_mutex, DESTROY);
// 	free(table->forks);
// 	free(table->philos);
// }

// static void free_philosophers(t_var *var)
// {
//     int i;

//     i = 0;
//     while (i < var->num_of_philo)
//     {
//         //     // if (var->philo[i] != NULL)
//         //     //     free(var->philo[i]);
//         // printf("ID:%d\n", var->philo[i].id);
//         i++;
//     }
// }

static void destroy_mutex(t_var *var)
{
    int i;

    i = 0;
    while (i < var->num_of_philo)
    {
        pthread_mutex_destroy(&var->forks[i]);
        pthread_mutex_destroy(&var->philo[i].lastmeal_mutex);
        i++;
    }
    pthread_mutex_destroy(&var->allready_mutex);
    pthread_mutex_destroy(&var->starttime_mutex);
    pthread_mutex_destroy(&var->isdead_mutex);
    pthread_mutex_destroy(&var->time2die_mutex);
    pthread_mutex_destroy(&var->deadindex_mutex);
    pthread_mutex_destroy(&var->deathtimestamp_mutex);
}

void clean(t_var *var, int level)
{
    if (level == 2)
        destroy_mutex(var);
    free(var->forks);
    free(var->philo);
    free(var->monitor);
}