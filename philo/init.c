/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:09:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/31 10:49:23 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_forks(t_table *table)
{
	int	i;

	table->fork_lock = malloc(sizeof(table->fork_lock) * table->phil_count);
	i = 0;
	while (i < table->phil_count)
	{
		if (pthread_mutex_init(&table->fork_lock[i], NULL))
			return (false);
		i++;
	}
	return (true);
}

static bool	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->start_lock, NULL))
		return (false);
	if (pthread_mutex_init(&table->print_lock, NULL))
		return (false);
	if (pthread_mutex_init(&table->maintenance, NULL))
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
		phil[i] = malloc(sizeof(t_phil) * 1);
		if (!phil[i])
			free_func(table);
		phil[i]->p = 0;
		phil[i]->id = i + 1;
		phil[i]->meals_eaten = 0;
		phil[i]->all_meals_eaten = 0;
		phil[i]->last_time_eat = table->sim_start_time;
		// printf("IN PHIL INIT: last meal: %llu\n", phil[i]->last_time_eat);
		if (pthread_mutex_init(&phil[i]->meal_lock, NULL))
			return (false);
		phil[i]->table = table;
		i++;
	}
	return (phil);
}

t_table	*init_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		free_func(table);
	table->phil_count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		table->meal_count = ft_atoi(av[5]);
	else
		table->meal_count = -1;
	// printf("table_meal_count: %i\n", table->meal_count);
	table->dead_flag = 0;
	table->dead_id = -1;
	table->sim_start_time = get_time();
	// printf("IN TABLE INIT: SIM START: %llu\n", table->sim_start_time);
	table->all_eat = 0;
	table->meal_flag = 0;
	table->phil = init_phil(ac, table);
	if (init_mutex(table) == false)
		return (0);
	if (init_forks(table) == false)
		return (0);
	return (table);
}
