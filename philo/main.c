/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/17 09:48:46 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
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
	t_main	main;
	// int i = 0;
	// while(av[i])
	// {
	// 	printf("av[%i]: %s\n", i, av[i]);
	// 	i++;
	// }
	main.phil_count = ft_atoi(av[1]);
	if (main.phil_count < 1)
		exit(1);
	main.time_to_die = ft_atoi(av[2]);
	// if (main.time_to_die == 0)
	// 	exit(1);
	main.time_to_eat = ft_atoi(av[3]);
	if (main.time_to_eat == 0)
		exit(1);
	main.time_to_sleep = ft_atoi(av[4]);
	// printf("%d\n", main.time_to_sleep);
	// if (main.time_to_sleep == 0)
	// 	exit(1);
	return (0);
}

void	*thinking()
{
	t_th	th;
	pthread_mutex_lock(&th.mutex);
	printf("philo thinking\n");
	pthread_mutex_unlock(&th.mutex);
}

int	create_threads(void)
{
	t_main	main;
	t_th	th;
	int		i;

	i = 0;
	pthread_mutex_init(&th.mutex, NULL);
	printf("main.phil_count: %i\n", main.phil_count);
	while (i <= main.phil_count)
	{
		if (pthread_create(&th.p[i], NULL, &thinking, NULL) != 0)
			return (1);
		printf("phil no.%i created\n", i);
		i++;
	}
	i = 0;
	while (i <= main.phil_count)
	{
		if (pthread_join(&th.p[i], NULL) != 0)
			return (1);
		printf("phil no.%i joined\n", i);
		i++;
	}
	pthread_mutex_destroy(&th.mutex);
	return (0);
}

int	main(int ac, char **av)
{
	if(ac < 5 || ac > 6)
		return(1);
	else
	{
		if (check_args(ac, av) != 0) // not zero means something wrong in arguments
			exit (1);
		if (get_args(av) != 0)
			exit (1);
		time(NULL);
		create_threads();
	}
	return(0);
}
