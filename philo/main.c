/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/11 11:35:11 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	stop(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->phil_count)
	{
		if (pthread_join(table->phil[i].p, NULL))
			return (false);
		i++;
	}
	i = 0;
	while (i < table->phil_count)
	{
		if (!pthread_mutex_destroy(table->fork_lock))
			return (false);
		i++;
	}
	pthread_mutex_destroy(&table->table_lock);
	pthread_mutex_destroy(&table->start_lock);
	pthread_mutex_destroy(&table->print_lock);
	return (true);
}

static bool	start(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->start_lock);
	while (i < table->phil_count)
	{
		if (pthread_create(&table->phil[i].p, NULL, &routine, &table->phil[i]))
			return (false);
		i++;
	}
	pthread_mutex_unlock(&table->start_lock);
	return (true);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (-1);
	if (valid_args(ac, av) == false)
		return (-1);
	if (init_table(ac, av, &table) == false)
		return (-1);
	if (start(&table) == true)
	{
		monitor(&table);
		stop(&table);
		free_func(&table);
	}
	return (0);
}
