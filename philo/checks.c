/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:21:00 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/05 16:13:25 by jhusso           ###   ########.fr       */
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
/* Here we have one Phil at a time:
	we check if the time_to_die has come.
We use Phils own lock because the only modifyable param we are wanting to read are
 phil->last_time_eat, and that can only be modified by Phils own thread in
 eat function, where it is protected with the same mutex. */

int	is_dead(t_phil *phil, t_table *table)
{
	// printf("***HERE***\n");
	pthread_mutex_lock(&table->table_lock);
	if (phil->table->time_to_die < (get_time() - phil->last_time_eat))
	{
		printf("%llu %i died", get_time() - phil->table->sim_start_time, phil->id);
		table->stop_flag = 1;
		pthread_mutex_unlock(&table->table_lock);
		return (0);
	}
	pthread_mutex_unlock(&table->table_lock);
	return (1);
}

/* The monitor is the one to put up the flags. This function is called
from print_status() and in print_status flags_up is protected with
table mutex. */

bool	died(t_phil *phil)
{
	if (phil->table->time_to_die <= (get_time() - phil->last_time_eat))
		return (true);
	return (false);
}
