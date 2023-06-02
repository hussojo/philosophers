/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:21:00 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/02 14:33:57 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_onlydig(char *c)
{
	while (*c)
	{
		if (*c < '0' || *c > '9')
			return (false);
		c++;
	}
	return (true);
}

bool	valid_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		if (is_onlydig(av[i]) == false)
			return (false);
		if (!ft_atoi(av[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_dead(t_phil *phil, t_table *table)
{
	pthread_mutex_lock(&phil->meal_lock);
	if (phil->table->time_to_die <= (get_time() - phil->last_time_eat))
	{
		phil->table->dead_flag = 1;
		printf("DEAD\n");
		pthread_mutex_unlock(&phil->meal_lock);
		return (true);
	}
	if (phil->meals_eaten >= table->meal_count && phil->all_meals == 0)
	{
		table->all_eat++;
		phil->all_meals = 1;
	}
	if (table->all_eat >= table->phil_count)
	{
		printf("EATEN\n");
		table->meal_flag = 1;
		pthread_mutex_unlock(&phil->meal_lock);
		return (true);
	}
	pthread_mutex_unlock(&phil->meal_lock);
	return (false);
}

// bool	all_meals_eaten(t_phil *phil, t_table *table)
// {
// 	//pthread_mutex_lock(&phil->meal_lock);
// 	if (phil->meals_eaten >= table->meal_count && phil->all_meals == 0)
// 	{
// 		table->all_eat++;
// 		phil->all_meals = 1;
// 	}
// 	if (table->all_eat >= table->phil_count)
// 	{
// 		table->meal_flag = 1;
// 		pthread_mutex_lock(&phil->meal_lock);
// 		return (true);
// 	}
// 	pthread_mutex_lock(&phil->meal_lock);
// 	return (false);
// }

bool	flags_up(t_phil *phil, t_table *table)
{
	pthread_mutex_lock(&phil->table->maintenance);
	if (table->dead_flag == 1 || table->meal_flag == 1)
	{
		pthread_mutex_unlock(&phil->table->maintenance);
		return (true);
	}
	pthread_mutex_unlock(&phil->table->maintenance);
	return (false);
}
