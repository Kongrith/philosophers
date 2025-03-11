/*
https://medium.com/@denaelgammal/dining-philosophers-problem-42-project-guide-mandatory-part-a20fb8dc530e


gettimeofday: is a function that helps you get the current time since a specific starting point (January 1, 1970).
To use gettimeofday function you need to use a struct named timeval a built-in structure defined in the <sys/time.h> header file.

When you define a variable from struct timeval and pass it to gettimeofday,
you will be able to access the current time in seconds with microseconds.
Timeval struct is defined like this:

struct timeval
{
	time_t			tv_sec;		// seconds
	suseconds_t		tv_usec;	// micro-seconds
}
*/
#include <sys/time.h>
#include <stdio.h>

int main()
{
	struct timeval time;
	gettimeofday(&time, NULL);	// get the current time

	long sec = time.tv_sec;		// seconds
	long usec = time.tv_usec;

	time_t msec = sec * 1000 + usec / 1000;
	printf("%ld\n", msec);
	return (0);
}
