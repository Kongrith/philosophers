#include "dining_philo.h"

/*
cc -pthread dining_philo.c init.c safe_functions.c dinner.c parsing.c getter_setter.c \
utils.c syncho_utils.c monitor.c write.c
./a.out 1 10 10 10

*/
int main(int ac, char **av)
{
	t_table table;
	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		error_exit("Wrong input:\n" G"Correct is ./philo 5 800 200 200 [5]"RST);
	}

	return (0);
}
