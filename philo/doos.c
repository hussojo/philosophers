/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/31 16:23:36 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_phil *phil)
{
	print_status(3, phil);
	ft_sleep(phil->table->time_to_sleep, phil);
	eat(phil);
}

void	eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->maintenance);
	if (flags_up(phil, phil->table) == true)
		stop(phil->table);
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
	// printf("phil[%i] mealss eaten: %i\n", phil->id, phil->meals_eaten);
	pthread_mutex_unlock(&phil->meal_lock);
	ft_sleep(phil->table->time_to_eat, phil);
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
		ft_sleep(phil->table->time_to_eat, phil);
		eat(phil);
	}
	return (NULL);
}

bool	monitor(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->maintenance);
	while (table->phil[i])
	{
		if (table->time_to_die <= (get_time() - table->phil[i]->last_time_eat))
		{
			table->dead_flag = 1;
			table->dead_id = table->phil[i]->id;
			return (false);
		}
		if (table->meal_count > 0)
		{
			if (table->phil[i]->meals_eaten >= table->meal_count // phil[i] meals eaten is read at the same time as updated in eat??
				&& table->phil[i]->all_meals_eaten == 0)
			{
				table->all_eat++;
				table->phil[i]->all_meals_eaten = 1;
			}
			if (table->all_eat >= table->phil_count)
			{
				table->meal_flag = 1;
				return (false);
			}
		}
		i++;
	}
	pthread_mutex_unlock(&table->maintenance);
	usleep(500);
	return (true);
}
