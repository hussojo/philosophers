/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/28 10:22:16 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_phil *phil)
{
	// THIS MAKES NO DIFFERENCE IN DYING ACCURACY
	// pthread_mutex_lock(&phil->table->maintenance);
	// set_flags(phil, phil->table);
	// pthread_mutex_unlock(&phil->table->maintenance);
	print_status(3, phil);
	ft_sleep(phil->table->time_to_sleep);
	eat(phil);
}

void	eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->maintenance);
	set_flags(phil, phil->table);
	pthread_mutex_unlock(&phil->table->maintenance);
	print_status(1, phil);
	pthread_mutex_lock(&phil->table->fork_lock[phil->id - 1]);
	print_status(5, phil);
	if (phil->id == phil->table->phil_count)
		pthread_mutex_lock(&phil->table->fork_lock[0]);
	else
		pthread_mutex_lock(&phil->table->fork_lock[phil->id]);
	print_status(6, phil);
	print_status(2, phil);
	pthread_mutex_lock(&phil->meal_lock);
	phil->last_time_eat = get_time();
	phil->meals_eaten++;
	ft_sleep(phil->table->time_to_eat);
	pthread_mutex_unlock(&phil->meal_lock);
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
bool	monitor(t_table *table)
{
	// printf("table->dead_flag : %i\n", table->dead_flag);
	if (table->dead_flag == 1)
	{
		printf("***\n returning false\n***\n");
		return (false);
	}
	if (table->meal_count > 0)
	{
		if (table->all_eat >= table->phil_count)
		{
			printf("***\n returning false\n***\n");
			return (false);
		}
	}
	// printf("***\n returning true\n***\n");
	return (true);
}
