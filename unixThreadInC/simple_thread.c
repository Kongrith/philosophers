#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*
Short introduction to threads (pthreads)
https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2

cc -pthread a.c
*/

void* routine()
{
	printf("Test from threads.\n");
	sleep(3);
	printf("Ending Threads.\n");
}

int main(int argc, char *argv[])
{
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
