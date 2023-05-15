/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/15 15:26:19 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_args(char ** av)
{
	t_philo	philo;
	// int i = 0;
	// while(av[i])
	// {
	// 	printf("av[%i]: %s\n", i, av[i]);
	// 	i++;
	// }
	philo.phil_count = ft_atoi(av[1]);
	if (philo.phil_count < 1)
		exit(1);
	if (ft_atoi(av[2]) <= 0)
		exit(1);
	if (ft_atoi(av[3]) <= 0)
		exit(1);
	if (ft_atoi(av[4]) <= 0)
		exit(1);
	return (0);
}

int	main(int ac, char **av)
{
	if(ac < 5 || ac > 6)
		return(0); // success for now
	else
	{
		get_args(av);
		printf("moi\n");
	}

	return(0);
}
