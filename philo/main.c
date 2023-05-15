/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/15 13:55:41 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_args(char ** av)
{
	// int i = 0;
	// while(av[i])
	// {
	// 	printf("av[%i]: %s\n", i, av[i]);
	// 	i++;
	// }
	if (ft_atoi(av[1]) < 1)
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
