# philosophers

//We need data structs:

	//For each philo, containing:
		//Philo ID, a thread
		//Fork pointers
		//Mutex
		//Whatever relevant to rules

	//For each fork
		//Mutex
		//ID

	//For the simulation data
		//Handle the mandatory rules
		//A pointer to the philo array (of structs)
		//A pointer to the fork array (of mutexes)
		//Mutex


//Write a skeleton in main()

	//Parse inputs
		//Convert each "time_to" inputs to milliseconds
		//Handle input errors
		//Handle the optional input of the total meals a philo must eat

	//Initialize data

		//malloc an array of philos
			//Initalize the philo data
			//Initialize the philo mutex before use

		//malloc an array of forks
			//Initialize the fork mutex before use
			//Assign left and right forks for each philo
			//Handle a single philo thread

	//Execute the simulation

		//Create a thread for each philo
		//Create a thread to check for deaths

		//Synchronise the philos eating to avoid deadlock/resouce contention
			//All even numbered philos eat while odds wait, and alternate
			//Utilize delay mechanisms like usleep() to avoid philos attempting busy forks

		//Print to the STDOUT the philo states with their timestamps
		//Don't forget to use pthread_join to wait for all threads to complete execution (the dining)

	//Clean up and free things to avoid memory leaks

### allowed functions
memset, printf, malloc, free, write

- usleep: Suspend the execution of a program to introduce a delay for a specified number of microseconds.
- gettimeofday: Obtain the current time.
- pthread_create: Create a new thread within a program.
- pthread_detach:_ Detach the newly created thread to allow it to run independently._
- pthread_join: Wait for the thread with ID thread_id to finish its execution.
- pthread_mutex_init: Initialize a mutex.
- pthread_mutex_destroy: Destroy the mutex after it has been used.
- pthread_mutex_lock: Lock the mutex before accessing and updating the shared data.
- pthread_mutex_unlock: Unlock the mutex, allowing other threads to access the shared resource.

#### Here are the things you need to know if you want to succeed this assignment:
- One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!


#### arrg

- `number_of_philosophers`: The number of philosophers and also the number
of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulatiion stops. If not specified, the simulation stops when a
philosopher dies.


- Each philosopher has a number ranging from 1 to number_of_philosophers.
- Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.



About the logs of your program:
```
[timestamp_in_ms] [X] has taken a fork
[timestamp_in_ms] [X] is eating
[timestamp_in_ms] [X] is sleeping
[timestamp_in_ms] [X] is thinking
[timestamp_in_ms] [X] died
```

- Any state change of a philosopher must be formatted as follows:
- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
- A displayed state message should not be mixed up with another message.
- A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.
- Again, philosophers should avoid dying!


The specific rules for the mandatory part are:
- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.


 Error Handling:

Does not crash or have undefined behaviour.
Does not have memory leaks.
No norm errors.
No global variables.
Defend if the program doesn't work on slower machines and test with modifying the thinking_time multiplier.
🔸 Code checks and rationale for each:

There is one thread per philosopher.
There is one fork per philosopher.
There is a mutex per fork. The mutex is used to check the fork value and/or change it.
The output view is never scrambled.
The death of a philospher can be checked.
There is a mutex to protect when a philosopher dies and starts eating at the same time.
🔸 Testing:

Should not test with more than 200 philosphers.
Should not test when either time_to_die, time_to_eat or time_to_sleep is under 60ms.
Test with 1 800 200 200: the philosopher should not eat and should die.
Test with 5 800 200 200: no one should die.
Test with 5 800 200 200 7: no one should die, and the simulation should stop when all the philosophers has eaten at least 7 times each.
Test with 4 410 200 200: no one should die.
Test with 4 310 200 100: one philosopher should die.
Test with 2 philosphers and check the different times: a death delayed by more than 10 ms is unacceptable.
Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time, that they don't steal forks, etc.
