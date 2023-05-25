/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:21:00 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/25 09:31:11 by jhusso           ###   ########.fr       */
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
	// unsigned long long	ts;
	unsigned long long	last_meal;

	// ts = get_time() - phil->table->sim_start_time;
	pthread_mutex_lock(&table->maintenance);
	last_meal = (get_time() - phil->last_time_eat);
	if (table->time_to_die < last_meal)
	{
		table->dead_flag = 1;
		// printf("%llu %u died\n", ts, phil->id);
		exit (0);
	}
	pthread_mutex_unlock(&table->maintenance);
}

void	all_meals(t_phil *phil, t_table *table)
{
	if (phil->meals_eaten >= table->meal_count)
		table->all_eat++;
	if (table->all_eat >= table->phil_count)
		table->meal_flag = 1;
}
	// i = 0;
	// while (i < table->phil_count)
	// {
	// 	if (table->dead_flag == 1)
	// 	{
	// 		printf("exiting!");
	// 		stop(table);
	// 		exit (0);
	// 	}
	// 	if (table->meal_count > 0)
	// 	{
	// 		if (table->phil[i]->meals_eaten >= table->meal_count)
	// 			table->all_eat++;
	// 		if (table->all_eat >= table->phil_count)
	// 			return(true);
	// 	}
	// }
	// return (false);

