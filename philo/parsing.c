/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:32:38 by khkomasa          #+#    #+#             */
/*   Updated: 2025/07/26 03:18:52 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_isspace(int ch)
{
	if ((9 <= ch && ch <= 13) || ch == 32)
	{
		return (1);
	}
	else
		return (0);
}

static int manage_character(char *str, int *ptr)
{
	int sign;
	int flag;
	int index;

	sign = 1;
	flag = 0;
	index = 0;
	while (ft_isspace(str[index]))
		index++;
	while (str[index] && (str[index] == '-' || str[index] == '+'))
	{
		if (str[index] == '-' && flag == 0)
		{
			sign = -1;
			flag = 1;
		}
		else if (str[index] == '+' && flag == 0)
			flag = 1;
		else
			return (0);
		index++;
	}
	*ptr = index;
	return (sign);
}

int ft_atoi(const char *str)
{
	int input_number;
	int sign;
	int index;

	sign = manage_character((char *)str, &index);
	if (sign == 0)
		return (0);
	input_number = 0;
	while ((str[index] != '\0') && ('0' <= str[index] && str[index] <= '9'))
	{
		input_number = 10 * input_number + (str[index] - '0');
		++index;
	}
	return (input_number * sign);
}

int parse_input(t_var *var, int argc, char *argv[])
{
	var->num_of_philo = ft_atoi(argv[1]);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	if (var->num_of_philo <= 0)
		return (error_exit(var->num_of_philo, "number of philo"));
	if (var->time_to_die <= 0)
		return (error_exit(var->time_to_die, "time_to_die"));
	if (var->time_to_eat <= 0)
		return (error_exit(var->time_to_eat, "time_to_eat"));
	if (var->time_to_sleep <= 0)
		return (error_exit(var->time_to_sleep, "time_to_sleep"));
	if (argc == 5)
		var->required_meals = -1;
	else
	{
		var->required_meals = ft_atoi(argv[5]);
		if (var->required_meals <= 0)
			return (error_exit(var->required_meals,
							   "number_of_times_each_philosopher_must_eat"));
	}
	return (0);
}
