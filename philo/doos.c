/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/05 16:02:24 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sleeping(t_phil *phil)
{
	if (!print_status("is sleeping", phil))
		return (0);
	ft_sleep(phil->table->time_to_sleep, phil);
	return (1);
}

static void	update_meals(t_phil *phil)
{
	phil->meals_eaten++;
	if (phil->meals_eaten >= phil->table->meal_count) // && phil->all_meals == 0
	{
		pthread_mutex_lock(&(phil->table->table_lock));
		phil->table->all_eat++;
		// phil->all_meals = 1;
		pthread_mutex_unlock(&(phil->table->table_lock));
	}
}

static int	eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->fork_lock[phil->id - 1]);
	if (!print_status("has taken a fork", phil))
		return (0);
	if (phil->id == phil->table->phil_count)
		pthread_mutex_lock(&phil->table->fork_lock[0]);
	else
		pthread_mutex_lock(&phil->table->fork_lock[phil->id]);
	if (!print_status("has taken a fork", phil))
		return (0);
	if (!print_status("is eating", phil))
		return (0);
	pthread_mutex_lock(&phil->phil_lock);
	phil->last_time_eat = get_time();
	pthread_mutex_unlock(&phil->phil_lock);
	update_meals(phil);
	ft_sleep(phil->table->time_to_eat, phil);
	if (phil->id == phil->table->phil_count)
		pthread_mutex_unlock(&phil->table->fork_lock[0]);
	else
		pthread_mutex_unlock(&phil->table->fork_lock[phil->id]);
	pthread_mutex_unlock(&phil->table->fork_lock[phil->id - 1]);
	return (1);
}

void	*routine(void *data)
{
	t_phil	*phil;

	phil = (t_phil *)data;
	pthread_mutex_lock(&phil->table->table_lock);
	pthread_mutex_unlock(&phil->table->table_lock);
	phil->last_time_eat = phil->table->sim_start_time;
	if ((phil->id % 2) == 0)
	{
		print_status("is thinking", phil);
		ft_sleep(5, phil);
	}
	while (1)
	{
		if (!eat(phil))
			break ;
		if (!sleeping(phil))
			break ;
		// if (print_status("is thinking", phil))
		// 	return (0);
	}
	return (NULL);
}


bool	monitor(t_table *table)
{
	int	i;
	int 	out;

	i = 0;
	out = 0;
	while (!out)
	{
		while (i < table->phil_count)
		{
			pthread_mutex_lock(&table->phil[i]->phil_lock);
			if (is_dead(table->phil[i], table) == 0)
			{
				// table->dead_flag = 1;
				print_status("died\n", table->phil[i]);
				out = 1;
				pthread_mutex_unlock(&table->phil[i]->phil_lock);
			}
			// printf("***HERE MONITOR***\n");
			// if (table->all_eat >= table->phil_count)
			// {
			// 	table->meal_flag = 1;
			// 	out = 1;
			// 	pthread_mutex_unlock(&table->table);
			// }
			pthread_mutex_unlock(&table->phil[i]->phil_lock);
			// if (out == 1)
			// 	return (false);
			i++;
		}
	}
	return (true);
}
