#include <unistd.h>
#include <stdio.h> //perror
#include <pthread.h>
#include <stdlib.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
	int index = *(int *)arg;
	int sum = 0;
	for (int j = 0; j < 5; j++)
		sum += primes[index + j];
	printf("local sum: %d\n", sum);
	*(int *)arg = sum;
	return arg;
}

/*
cc -pthread sum_num_in_arr.c

https://www.youtube.com/watch?v=Adtrk3PREQI&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=9
*/
int main(int argc, char *argv[])
{
	pthread_t th[2];
	int i = 0;
	for (i = 0; i < 2; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Fail to create thread");
	}
	int globalSum = 0;
	for (i = 0; i < 2; i++)
	{
		int *result;
		if (pthread_join(th[i], (void **) &result) != 0)
			perror("Fail to join thread");
		globalSum += *result;
		free(result);
	}
	printf("%d\n", globalSum);
	return (0);
}
