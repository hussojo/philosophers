/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:09:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/19 11:10:11 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->start_lock, NULL))
		return (false);
	if (pthread_mutex_init(&table->stop_lock, NULL))
		return (false);
	return (true);
}

t_phil	**init_phil(int ac, t_table *table)
{
	t_phil	**phil;
	int		i;

	phil = malloc(sizeof(t_phil) * table->phil_count);
	if (!phil)
		exit (1);
	i = 0;
	while (i < table->phil_count)
	{
		phil[i] = malloc(sizeof(t_phil));
		phil[i]->id = i + 1;
		phil[i]->last_time_eat = 0;
		phil[i]->table = table;
		printf("phil no. %i created\n", phil[i]->id);
		i++;
	}
	return (phil);
}

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	table->phil_count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meal_count = ft_atoi(av[5]);
	else
		table->meal_count = -1;
	table->phil = init_phil(ac, table);
	if (init_mutex(table) == false)
		return (0);
	return (table);
}
