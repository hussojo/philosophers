/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/22 15:11:02 by jhusso           ###   ########.fr       */
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
	pthread_mutex_lock(&phil->table->fork_lock[phil->id - 1]);
	print_status(5, phil);
	if (phil->id == phil->table->phil_count)
	{
		// printf("*****\nHERE\n*****\n");
		pthread_mutex_lock(&phil->table->fork_lock[0]);
	}
	else
		pthread_mutex_lock(&phil->table->fork_lock[phil->id]);
	print_status(5, phil);
	pthread_mutex_lock(&phil->table->start_lock);
	print_status(2, phil);
	phil->last_time_eat = get_time();
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->table->start_lock);
	ft_sleep(phil->table->time_to_eat);
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
		think(phil);
	else
		eat(phil);
	// print_status(1, phil);
	return (NULL);
}

bool	monitor(t_table *table) // is_dead()
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
			exit (0); // PROBLEM
			// if (stop(table) == true)
			// 	return (true);
		}
		if (table->meal_count > 0)
		{
			if (table->phil[i]->meals_eaten >= table->meal_count)
			{
				table->all_eat++;
				printf("%i\n", table->all_eat);
			}
			if (table->all_eat >= table->phil_count)
			{
				if (stop(table) == true)
					return (true);
			}
		}
	}
	return (false);
}
