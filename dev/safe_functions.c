#include "dining_philo.h"

/*
Module containing wrapper functions with embeded controls on return
*/
void	*safe_malloc(size_t bytes)
{
	void *ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("abcde");
	return (ret);
}

/*
*/
static void handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return;
	if (EINVAL == status && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid.");
	else if (EINVAL == status && opcode == INIT)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread blocked waiting for mutex.");
	else if (EPERM == status)
		error_exit("the current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		error_exit("the process cannot allocate enough memory to create another mutex.");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

/*	MUTEX SAFE
	init
	destroy
	lock
	unlock
*/
void safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("wrong mutex code");
}

/* THREADS
*/

static void handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return;
	if (status == EAGAIN)
		error_exit("No resource to create another thread.");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permission.");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The status specified by attr is invalid");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is not joinable.");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that specified by the given thread ID, thread");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of thread specified the calling thread.");
}

void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("dgsdg");
}
