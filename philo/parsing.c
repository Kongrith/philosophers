/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:32:38 by khkomasa          #+#    #+#             */
/*   Updated: 2025/03/06 14:23:27 by toon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int len;
	const char *number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Input number should be positive number");
	if (!is_digit(*str))
		error_exit("Input number should be digit");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("Input value exceeds maximum int");
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
		error_exit("Input value exceeds maximum int");
	return (num);
}

void parse_input(t_var *var, int argc, char *argv[])
{
	var->num_of_philo = ft_atoi(argv[1]);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	printf("Num Philo: %d", var->num_of_philo);
	printf("Time2Die: %ld", var->time_to_die);
	printf("Time2Eat: %ld", var->time_to_eat);
	printf("Time2Sleep: %ld", var->time_to_sleep);
	if (argc == 5)
		var->limit_meals = -1;
	else
		var->limit_meals = ft_atoi(argv[5]);
	if ((var->num_of_philo <= 0) || (var->time_to_die <= 0) || (var->time_to_eat) <= 0 || (var->time_to_sleep <= 0))
		error_exit("Value is less than zero");
}
