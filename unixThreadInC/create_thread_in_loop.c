#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*
create_thread_in_loop
https://www.youtube.com/watch?v=xoXzp4B8aQk&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=6

cc -pthread create_thread_in_loop.c
*/

int mails = 0;
pthread_mutex_t mutex;		// protect other thread exec in the same time

void *routine()
{
	/*	read variable
		increament
		update variable
	*/
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

int main(int argc, char *argv[])
{
	pthread_t th[4];
	int i;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		if (pthread_create(th + i, NULL, &routine, NULL))
		{
			perror("Fail to create thread !!");
			return 1;
		}
		printf("Thread: %d starting ..\n", i);
		// if (pthread_join(th[i], NULL) != 0)
		// 	return 2;
		// printf("Thread: %d ending ..\n", i);
	}
	for (i = 0; i < 4; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			return 2;
		printf("Thread: %d ending ..\n", i);
	}
		pthread_mutex_destroy(&mutex);
	printf("mails: %d\n", mails);
	return 0;
}
