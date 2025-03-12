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

static bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool is_space(char ch)
{
	return ((9 <= ch && ch <= 13) || ch == 32);
}

/*
The allowable number: equal or greater than zero
return:
	 0 to +Int: OK
	-1        : error
*/
int check_input(const char *str)
{
	int i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	if (!is_digit(str[i]))
		return (-2);
	return (i);
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

	Normal Case: equal or greater than zero
	Error Case : -1
*/
long ft_atoi(const char *str)
{
	int i;
	int ret;
	long num;

	num = 0;
	ret = check_input(str);
	if (ret < 0)
		return (ret);
	else
		i = ret;
	while (is_digit(str[i]))
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	if (num < INT_MIN || num > INT_MAX)
		return (-3);
	return (num);
}

int parse_input(t_var *var, int argc, char *argv[])
{
	var->num_of_philo = ft_atoi(argv[1]);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	printf("Num Philo: %d\n", var->num_of_philo);
	printf("Time2Die: %ld\n", var->time_to_die);
	printf("Time2Eat: %ld\n", var->time_to_eat);
	printf("Time2Sleep: %ld\n", var->time_to_sleep);
	if (argc == 5)
		var->required_meals = -1;
	else
		var->required_meals = ft_atoi(argv[5]);
	// if ((var->num_of_philo <= 0) || (var->time_to_die <= 0) || (var->time_to_eat) <= 0 || (var->time_to_sleep <= 0))
	// 	error_exit("Value is less than zero");
	return (0);
}