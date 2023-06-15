/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 08:38:03 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/15 09:30:57 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_dead(t_phil *phil, t_table *table)
{
	pthread_mutex_lock(&phil->meal_lock);
	if (phil->table->time_to_die <= (get_time() - phil->last_time_eat))
	{
		printf("%zu %u died\n", (get_time() - table->sim_start_time), phil->id);
		flags_up(table, 1);
		pthread_mutex_unlock(&phil->meal_lock);
		return (true);
	}
	pthread_mutex_unlock(&phil->meal_lock);
	pthread_mutex_lock(&phil->table->table_lock);
	if (table->all_meals_eaten >= table->phil_count)
	{
		flags_up(table, 1);
		pthread_mutex_unlock(&phil->table->table_lock);
		return (true);
	}
	pthread_mutex_unlock(&phil->table->table_lock);
	return (false);
}

bool	flags_up(t_table *table, int flag)
{
	if (flag == 1)
	{
		table->stop_flag = 1;
		return (true);
	}
	if (table->stop_flag == 1)
		return (true);
	return (false);
}

bool	monitor(t_table *table)
{
	int	i;
	int	exit;

	exit = 0;
	while (!exit)
	{
		i = 0;
		while (i < table->phil_count)
		{
			if (is_dead(&table->phil[i], table) == true)
			{
				exit = 1;
				break ;
			}
			i++;
		}
		usleep(250);
	}
	return (true);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else
		return (0);
}

void	ft_sleep(size_t ms, t_phil *phil)
{
	size_t	time;

	time = get_time();
	while ((get_time() - time) < ms && flags_up(phil->table, 0) == false)
	{
		usleep (500);
	}
}
