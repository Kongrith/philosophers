#include "philo.h"

/*
We need data structs:
	For each philo, containing:
		Philo ID, a thread ✅
		Fork pointers
		Mutex
		Whatever relevant to rules

	For each fork
		Mutex
		ID

	For the simulation data
		Handle the mandatory rules
		A pointer to the philo array (of structs)
		A pointer to the fork array (of mutexes)
		Mutex


Write a skeleton in main()
	Parse inputs
		Convert each "time_to" inputs to milliseconds
		Handle input errors
		Handle the optional input of the total meals a philo must eat

	Initialize data
		malloc an array of philos
			Initalize the philo data
			Initialize the philo mutex before use

		malloc an array of forks
			Initialize the fork mutex before use
			Assign left and right forks for each philo
			Handle a single philo thread

	Execute the simulation

		Create a thread for each philo
		Create a thread to check for deaths

		Synchronise the philos eating to avoid deadlock/resouce contention
			All even numbered philos eat while odds wait, and alternate
			Utilize delay mechanisms like usleep() to avoid philos attempting busy forks

		Print to the STDOUT the philo states with their timestamps
		Don't forget to use pthread_join to wait for all threads to complete execution (the dining)

	Clean up and free things to avoid memory leaks

./philo 1 800 200 200
*/
int main(int argc, char *argv[])
{
	t_var var;

	if (argc == 5 || argc == 6)
	{
		parse_input(&var, argc, argv);
		initialization(&var);
		start_simulation(&var);
		// clean
	}
	else
	{
		error_exit("wrong input");
	}
	return (0);
}
