/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:09:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/11 08:05:38 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_forks(t_table *table)
{
	int	i;

	table->fork_lock = malloc(sizeof(pthread_mutex_t) * table->phil_count);
	if (!table->fork_lock)
		return (false);
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
	if (pthread_mutex_init(&table->table_lock, NULL))
		return (false);
	if (init_forks(table) == false)
		return (false);
	return (true);
}

static bool	init_phil(t_table *table)
{
	int	i;

	table->phil = malloc(sizeof(t_phil) * table->phil_count);
	if (!table->phil)
		return (false);
	i = 0;
	while (i < table->phil_count)
	{
		table->phil[i].p = 0;
		table->phil[i].id = i + 1;
		table->phil[i].meals_eaten = 0;
		table->phil[i].last_time_eat = table->sim_start_time;
		if (pthread_mutex_init(&table->phil[i].meal_lock, NULL))
			return (false);
		table->phil[i].table = table;
		i++;
	}
	return (true);
}

static bool	init_args(t_table *table, char **av)
{
	table->phil_count = ft_unsigned_atoi(av[1]);
	if (table->phil_count < 1 || table->phil_count > 200)
		return (false);
	table->time_to_die = ft_unsigned_atoi(av[2]);
	table->time_to_eat = ft_unsigned_atoi(av[3]);
	table->time_to_sleep = ft_unsigned_atoi(av[4]);
	if (av[5])
		table->meal_count = ft_unsigned_atoi(av[5]);
	else
		table->meal_count = -1;
	return (true);
}

bool	init_table(int ac, char **av, t_table *table)
{
	if (init_args(table, av) == false)
		return (false);
	table->sim_start_time = get_time();
	if (table->sim_start_time == 0)
		return (false);
	table->stop_flag = 0;
	table->all_meals_eaten = 0;
	table->meal_flag = 0;
	if (init_phil(table) == false)
		return (false);
	if (init_mutex(table) == false)
	{
		free_func(table);
		return (false);
	}
	return (true);
}
