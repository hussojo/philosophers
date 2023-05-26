/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:21:00 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/26 11:25:30 by jhusso           ###   ########.fr       */
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

void	is_dead(t_phil *phil, t_table *table)
{
	unsigned long long	last_meal;

	last_meal = (get_time() - phil->last_time_eat);
	if (table->time_to_die < last_meal)
	{
		table->dead_flag = 1;
		exit (0);
	}
}

void	all_meals(t_phil *phil, t_table *table)
{
	if (phil->meals_eaten >= table->meal_count)
		table->all_eat++;
	if (table->all_eat >= table->phil_count)
		table->meal_flag = 1;
}

void	set_flags(t_phil *phil, t_table *table)
{
	is_dead(phil, phil->table);
	all_meals(phil, phil->table);
}
