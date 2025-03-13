#include "philo.h"

long get_long(pthread_mutex_t *mutex, long value)
{
    long ret;
    pthread_mutex_lock(mutex);
    ret = value;
    pthread_mutex_unlock(mutex);
    return (ret);
}

void set_long(pthread_mutex_t *mutex, long *dest, long value)
{
    pthread_mutex_lock(mutex);
    *dest = value;
    pthread_mutex_unlock(mutex);
}