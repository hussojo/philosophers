/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/16 08:41:52 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	// printf("ac: %i\n", ac);
	while (i < ac)
	{
		// printf("ac:%i\n", i);
		j = 0;
		if (av[i][j] > '0' && av[i][j] < '9')
		{
			// printf("av[%i][%i]: %c\n", i, j, av[i][j]);
			j++;
		}
		else
			return (1);
		i++;
	}
	return (0);
}

int	get_args(char ** av)
{
	t_philo	philo;
	// int i = 0;
	// while(av[i])
	// {
	// 	printf("av[%i]: %s\n", i, av[i]);
	// 	i++;
	// }
	// philo.phil_count = ft_atoi(av[1]);
	// if (philo.phil_count < 1)
	// 	exit(1);
	// if (ft_atoi(av[2]) <= 0)
	// 	exit(1);
	// if (ft_atoi(av[3]) <= 0)
	// 	exit(1);
	// if (ft_atoi(av[4]) <= 0)
	// 	exit(1);
	return (0);
}

int	main(int ac, char **av)
{
	if(ac < 5 || ac > 6)
		return(0); // success for now
	else
	{
		if (check_args(ac, av) != 0) // not zero means something wrong in arguments
			exit (1);
		// if (get_args(av) ! = 0);
	}

	return(0);
}
