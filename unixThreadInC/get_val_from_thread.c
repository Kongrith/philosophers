#include <pthread.h>
#include <time.h>
#include <stdlib.h> // สำหรับ srand
#include <stdio.h>

void *roll_dice()
{
	int value = (rand() % 6) + 1;
	int *result = malloc(sizeof(int));
	*result = value;
	// printf("%d\n", value);
	printf("%p\n", result);
	return (void *)result;
}

/*
cc get_val_from_thread.c -pthread
https://www.youtube.com/watch?v=ln3el6PR__Q&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=7
*/
int main(int argc, char *argv[])
{
	int *result;
	pthread_t th;
	srand(time(NULL));
	if (pthread_create(&th, NULL, &roll_dice, NULL))
		return (1);
	if (pthread_join(th, (void **) &result))
		return (2);
	printf("%d\n", *result);
	printf("%p\n", result);
	return (0);
}
