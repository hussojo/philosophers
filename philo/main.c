/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/26 11:41:54 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop(t_table *table)
{
	int	i;

	i = 0;
	printf("*****\nHERE stop\n*****\n");
	print_status(4, *table->phil);
	pthread_mutex_destroy(&table->maintenance);
	pthread_mutex_destroy(&table->start_lock);
	pthread_mutex_destroy(&table->print_lock);
	i = 0;
	while (i < table->phil_count)
	{
		pthread_mutex_destroy(table->fork_lock);
		i++;
	}
	exit(0);
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
		if (monitor(table) == false)
		{
			printf("*****\nHERE MAIN\n*****\n");
			stop(table);
			// system("leaks philo");
			// exit (1);
			// stop(table);
			// free_func(table);
		}
	}
	return (0);
}
