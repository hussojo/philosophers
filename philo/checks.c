/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:21:00 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/31 16:25:46 by jhusso           ###   ########.fr       */
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

// bool	is_dead(t_phil *phil, t_table *table)
// {
// 	// printf("HOXHOXHOX");
// 	// printf("table->time_to_die: %u\n", table->time_to_die);
// 	// printf("time since last meal %i: %llu\n", phil->id, get_time() - phil->last_time_eat);
// 	if (table->time_to_die <= (get_time() - phil->last_time_eat))
// 	{
// 		table->dead_flag = 1;
// 		table->dead_id = phil->id;
// 		return (true);
// 	}
// 	return (false);
// }

// bool	all_meals_eaten(t_phil *phil, t_table *table)
// {
// 	if (phil->meals_eaten >= table->meal_count && phil->all_meals_eaten == 0)
// 		{
// 			table->all_eat++;
// 			// printf("table->all_eat by phil[%i]: %i\n", phil->id, table->all_eat);
// 			phil->all_meals_eaten = 1;
// 		}
// 	if (table->all_eat >= table->phil_count)
// 	{
// 		table->meal_flag = 1;
// 		// printf("table->meal_flag: %i\n", table->meal_flag);
// 		return (true);
// 	}
// 	return (false);
// }

bool	flags_up(t_phil *phil, t_table *table)
{
	if (table->dead_flag == 1 || table->meal_flag == 1)
		stop(table);
	return (false);
}
