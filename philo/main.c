/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/18 11:37:11 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_args(char ** av, t_args *args)
{
	// t_args	args;
	// int i = 0;
	// while(av[i])
	// {
	// 	printf("av[%i]: %s\n", i, av[i]);
	// 	i++;
	// }
	args->phil_count = ft_atoi(av[1]);
	printf("Phil count: %d\n", args->phil_count);
	// if (args->phil_count < 1)
	// 	exit(1);
	args->time_to_die = ft_atoi(av[2]);
	printf("time to die: %d\n", args->time_to_die);
	if (args->time_to_die == 0)
		exit(1);
	args->time_to_eat = ft_atoi(av[3]);
	printf("time to eat: %d\n", args->time_to_eat);
	// if (args->time_to_eat == 0)
	// 	exit(1);
	args->time_to_sleep = ft_atoi(av[4]);
	printf("time to sleep: %d\n", args->time_to_sleep);
	// if (args->time_to_sleep == 0)
	// 	exit(1);
	args->meal_count = ft_atoi(av[5]);
	printf("meal count: %d\n", args->meal_count);
	// if (args->meal_count == 0)
	// 	exit(1);
	return (0);
}

void	init_phil(t_phil *phil, int start_time)
{
	// phil->id = id;
	phil->last_time_eat = start_time;
}

int	main(int ac, char **av)
{
	t_phil			*phil;
	t_args			*args;
	unsigned int	start_time;

	if(ac < 5 || ac > 6)
		return(1);
	else
	{
		if (check_args(ac, av)) // not zero means something wrong in arguments
			exit (1);
		// create_threads();
	}
	return(0);
}
