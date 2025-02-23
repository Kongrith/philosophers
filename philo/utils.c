#include "philo.h"

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

void error_exit(char *str)
{
	printf("%s\n", str);
}
