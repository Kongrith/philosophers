#include "philo.h"

static inline bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

/*
	1) check for negatives
	2) check if the number is legit e.g.,   "  +77$%"
											"  +&%42 "
	3) check for INT_MAX e.g., 223593333333368
		check for len 2_147_483_647 if len > 10, sure > INT_MAX
		(2_147_483_647 -> 9_999_999_999) still to check

	why return ptr?		"   +77&%$""
					ret		 /\
*/
static const char *valid_input(const char *str)
{
	int len; // len of str
	const char *number;

	len = 0;
	// skip the spaces
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("value");
	if (!is_digit(*str))
		error_exit("digt");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("int max");
	return (number);
}

static long ft_atoi(const char *str)
{
	long num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("max");
	return (num);
}

void parse_input(t_var *var, int argc, char *argv[])
{
	var->num_of_philo = ft_atoi(argv[1]);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		var->limit_meals = -1;
	else
		var->limit_meals = ft_atoi(argv[5]);
	// if (table->time_to_die < 6000 || table->time_to_eat < 6000 || table->time_to_sleep < 6000)
	// 	error_exit("asd");
	// if (av[5])
	// 	table->nbr_limit_meals = ft_atoi(av[5]);
	// else
	// 	table->nbr_limit_meals = -1;

	// printf("%ld\n", var->time_to_die);
	// printf("%ld\n", var->time_to_eat);
	// printf("%ld\n", var->time_to_sleep);
}
