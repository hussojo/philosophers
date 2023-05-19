/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/19 08:49:46 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	start(t_table *table)
{
	int	i;

	// table->sim_start_time = get_time(); is this the right place?
	i = 0;
	while (i <= table->phil_count)
	{
		if (pthread_create(&table->phil[i]->p, NULL, &think, table->phil[i]))
			return (false);
		printf("thread no. %i created\n", i + 1);
		i++;
	}
	printf("%i\n", pthread_create(&table->watcher, NULL, &monitor, NULL));
	if (pthread_create(&table->watcher, NULL, &monitor, NULL))
		return (false);
	return (true);
}

static bool	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->start_lock, NULL))
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
	// printf("meal count: %d\n", table->meal_count);
	table->phil = init_phil(ac, table);
	if (init_mutex(table) == false)
		return (0);
	return (table);
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
	return (0);
}
