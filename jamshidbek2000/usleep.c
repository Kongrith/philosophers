/*
สาธิต usleep ที่ไม่ได้เที่ยงตรงจริงๆ
ref: https://github.com/Jamshidbek2000/philosophers_42/blob/master/explanation/usleep.c

struct timeval {
	time_t			tv_sec;			// seconds
	suseconds_t		tv_usec;		// microseconds
};
*/

#include <unistd.h>	// usleep
#include <sys/time.h> // time รวมถึง timeval
#include <stdio.h>

void exmaple()
{
	struct timeval	start_time;
	struct timeval	end_time;
	long requested_sleep_time;
	long actual_sleep_time;

	requested_sleep_time = 200 * 1000; // micro second
	gettimeofday(&start_time, NULL);
	usleep(requested_sleep_time);
	gettimeofday(&end_time, NULL);
	actual_sleep_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);

	printf("Requested Sleep Time: %ld microseconds\n", requested_sleep_time);
	printf("Actual Sleep Time: %ld microseconds\n", actual_sleep_time);
}

int main()
{
	exmaple();
	return (0);
}
