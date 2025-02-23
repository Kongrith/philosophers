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
