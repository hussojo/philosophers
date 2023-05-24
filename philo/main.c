/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/24 11:29:35 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop(t_table *table)
{
	int	i;
	// printf("*****\nHERE STOP\n*****\n");
	i = 0;
	// printf("Nroof Phil: %d\n", table->phil_count);
	while (i < table->phil_count)
	{
		printf("i=%d\n", i);
		printf("*****\nHERE STOP EXIT\n*****\n");
		if (pthread_join(table->phil[i]->p, NULL))
			exit (-1);
		i++;
	}
	pthread_mutex_destroy(&table->start_lock);
	pthread_mutex_destroy(&table->print_lock);
	i = 0;
	while (i < table->phil_count)
	{
		pthread_mutex_destroy(table->fork_lock);
		i++;
	}
	printf("*****\nHERE STOP\n*****\n");
	free_func(table);
}

static bool	start(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->phil_count)
	{
		if (pthread_create(&table->phil[i]->p, NULL, &routine, table->phil[i]))
			return (false);
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_phil			*phil;
	t_table			*table;
	unsigned int	start_time;

	if (ac < 5 || ac > 6)
		exit (1);
	if (valid_args(ac, av) == false)
		exit (1);
	table = init_table(ac, av);
	if (!table)
		exit (1);
	start(table);
	while (42)
	{
		if (is_dead(table) == true)
		{
			printf("*****\nHERE MAIN\n*****\n");
			stop(table);
			// free_func(table);
		}
	}
	return (0);
}
