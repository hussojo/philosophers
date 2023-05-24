/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/24 11:22:52 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_phil *phil)
{
	print_status(3, phil);
	ft_sleep(phil->table->time_to_sleep);
	// think(phil);
	eat(phil);
}

void	eat(t_phil *phil)
{
	print_status(1, phil);
	pthread_mutex_lock(&phil->table->fork_lock[phil->id - 1]);
	print_status(5, phil);
	if (phil->id == phil->table->phil_count)
		pthread_mutex_lock(&phil->table->fork_lock[0]);
	else
		pthread_mutex_lock(&phil->table->fork_lock[phil->id]);
	print_status(6, phil);
	pthread_mutex_lock(&phil->table->start_lock);
	print_status(2, phil);
	phil->last_time_eat = get_time();
	phil->meals_eaten++;
	ft_sleep(phil->table->time_to_eat);
	pthread_mutex_unlock(&phil->table->start_lock);
	if (phil->id == phil->table->phil_count)
		pthread_mutex_unlock(&phil->table->fork_lock[0]);
	else
		pthread_mutex_unlock(&phil->table->fork_lock[phil->id]);
	pthread_mutex_unlock(&phil->table->fork_lock[phil->id - 1]);
	sleeping(phil);
}

void	*routine(void *data)
{
	t_phil				*phil;

	phil = (t_phil *)data;
	pthread_mutex_lock(&phil->table->start_lock);
	pthread_mutex_unlock(&phil->table->start_lock);
	if ((phil->id % 2) == 0)
		eat(phil);
	else
	{
		print_status(1, phil);
		ft_sleep(phil->table->time_to_eat);
		eat(phil);
	}
	return (NULL);
}

bool	is_dead(t_table *table)
{
	int					i;
	unsigned long long	last_meal;
	unsigned long long	ts;

	i = 0;
	while (i < table->phil_count)
	{
		last_meal = (get_time() - table->phil[i]->last_time_eat);
		ts = get_time() - table->sim_start_time;
		if (table->time_to_die < last_meal)
		{
			table->dead = 1;
			printf("%llu %u died\n", ts, table->phil[i]->id);
			stop(table);
			return (true);
		}
		if (table->dead == 1)
			stop(table);
		if (table->meal_count > 0)
		{
			if (table->phil[i]->meals_eaten >= table->meal_count)
				table->all_eat++;
			if (table->all_eat >= table->phil_count)
				return(true);
		}
	}
	return (false);
}
