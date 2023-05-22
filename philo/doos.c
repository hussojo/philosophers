/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/22 10:26:56 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_phil *phil)
{
	print_status(3, phil);
	ft_sleep(phil->table->time_to_sleep);
	think(phil);
}

void	eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->fork_lock[phil->id]);
	print_status(5, phil);
	pthread_mutex_lock(&phil->table->fork_lock[phil->id + 1]);
	print_status(5, phil);
	pthread_mutex_lock(&phil->table->start_lock);
	print_status(2, phil);
	phil->last_time_eat = get_time();
	phil->meals_eaten++;
	ft_sleep(phil->table->time_to_eat);
	pthread_mutex_unlock(&phil->table->start_lock);
	pthread_mutex_unlock(&phil->table->fork_lock[phil->id + 1]);
	pthread_mutex_unlock(&phil->table->fork_lock[phil->id]);
	sleeping(phil);
}

void	think(t_phil *phil)
{
	print_status(1, phil);
	ft_sleep(phil->table->time_to_eat);
	eat(phil);
}

void	*routine(void *data)
{
	t_phil				*phil;
	unsigned long long	time;

	phil = (t_phil *)data;
	// printf("Phil nro %i was here\n", phil->id);
	pthread_mutex_lock(&phil->table->start_lock);
	pthread_mutex_unlock(&phil->table->start_lock);
	if ((phil->id % 2) == 0)
		eat(phil);
	else
		think(phil);
	// print_status(1, phil);
	return (NULL);
}

void	monitor(t_table *table)
{
	int					i;
	unsigned long long	last_meal;

	i = 0;
	while (i < table->phil_count)
	{
		last_meal = (get_time() - table->phil[i]->last_time_eat);
		if (table->time_to_die < last_meal)
		{
			print_status(4, table->phil[i]);
			// if (stop(table) == false)
			// 	exit(1);
			// else
			free_func(table);
		}
		if (table->phil[i]->meals_eaten >= table->meal_count)
		{
			// print_status(6, *table->phil);
			table->all_eat++;
		}
		if (table->all_eat >= table->phil_count)
		{
			free_func(table);
			exit (0);
		}

	}

}
