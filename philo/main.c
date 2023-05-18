/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/18 12:02:39 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table->phil_count = ft_atoi(av[1]);
	// printf("Phil count: %d\n", table->phil_count);
	// if (table->phil_count < 1)
	// return (false);
	table->time_to_die = ft_atoi(av[2]);
	printf("time to die: %d\n", table->time_to_die);
	if (table->time_to_die == 0)
		return (false);
	table->time_to_eat = ft_atoi(av[3]);
	printf("time to eat: %d\n", table->time_to_eat);
	// if (table->time_to_eat == 0)
	// 	return (false);
	table->time_to_sleep = ft_atoi(av[4]);
	printf("time to sleep: %d\n", table->time_to_sleep);
	// if (table->time_to_sleep == 0)
	// 	return (false);
	table->meal_count = ft_atoi(av[5]);
	printf("meal count: %d\n", table->meal_count);
	// if (table->meal_count == 0)
	// 	return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_phil			*phil;
	t_table			*table;
	unsigned int	start_time;

	if (ac < 5 || ac > 6)
		return (1);
	else
	{
		if (valid_args(ac, av) == false)
			exit (1);
		table = init_table(ac, av);
		if (table == false)
			exit (1);
		// create_threads();
	}
	return (0);
}
