#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*
mutex
https://www.youtube.com/watch?v=oq29KUy29iQ&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=5

cc -pthread mutex.c
*/

int mails = 0;
int lock = 0;
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
	pthread_t t1;
	pthread_t t2;
	pthread_mutex_init(&mutex, NULL);

	if (pthread_create(&t1, NULL, &routine, NULL))
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL))
		return 2;
	if (pthread_join(t1, NULL))
		return 3;
	if (pthread_join(t2, NULL))
		return 3;

	pthread_mutex_destroy(&mutex);
	printf("mails: %d\n", mails);
	return 0;
}
