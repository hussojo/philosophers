/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/19 13:56:14 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	stop(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->phil_count)
	{
		if (pthread_join(table->phil[i]->p, NULL))
			return (false);
		else
			printf("thread no. %i joined\n", i + 1);
		i++;
	}
	if (pthread_join(table->watcher, NULL))
		return (false);
	else
		printf("watcher joined\n");
	pthread_mutex_destroy(&table->start_lock);
	free_func(table);
	return (true);
}

static bool	start(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->phil_count)
	{
		if (pthread_create(&table->phil[i]->p, NULL, &think, table->phil[i]) != 0)
			return (false);
		else
			printf("thread no. %i created\n", i + 1);
		i++;
	}
	if (pthread_create(&table->watcher, NULL, &monitor, table))
		return (false);
	table->sim_start_time = get_time();
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
	stop(table);
	return (0);
}
