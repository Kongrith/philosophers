/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toon <toon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:32:51 by khkomasa          #+#    #+#             */
/*   Updated: 2025/03/06 14:21:32 by toon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
./philo 1 800 200 200
./philo 4 410 200 200		one philosopher should die
*/
int main(int argc, char *argv[])
{
	t_var var;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&var, argc, argv) < 0)
			return (0);
		if (initialization(&var) < 0)
			return (0);
		printf("I am here\n");
		start_simulation(&var);
		// clean();
	}
	else
		error_exit(-1, "Invalid Input Agruments");
	return (0);
}
