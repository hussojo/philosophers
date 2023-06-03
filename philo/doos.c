/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/03 10:53:19 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sleeping(t_phil *phil)
{
	if (print_status("is sleeping", phil))
		ft_sleep(phil->table->time_to_sleep, phil);
	if (flags_up(phil, phil->table) == true)
		return (0);
	print_status("is thinking", phil);
	return (1);
}

static int	eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->fork_lock[phil->id - 1]);
	print_status("has taken a fork", phil);
	if (phil->id == phil->table->phil_count)
		pthread_mutex_lock(&phil->table->fork_lock[0]);
	else
		pthread_mutex_lock(&phil->table->fork_lock[phil->id]);
	print_status("has taken a fork", phil);
	print_status("is eating", phil);
	pthread_mutex_lock(&phil->meal_lock);
	phil->last_time_eat = get_time();
	phil->meals_eaten++;
	pthread_mutex_unlock(&phil->meal_lock);
	ft_sleep(phil->table->time_to_eat, phil);
	if (phil->id == phil->table->phil_count)
		pthread_mutex_unlock(&phil->table->fork_lock[0]);
	else
		pthread_mutex_unlock(&phil->table->fork_lock[phil->id]);
	pthread_mutex_unlock(&phil->table->fork_lock[phil->id - 1]);
	if (flags_up(phil, phil->table) == true)
		return (0);
	return (1);
}

void	*routine(void *data)
{
	t_phil	*phil;

	phil = (t_phil *)data;
	pthread_mutex_lock(&phil->table->start_lock);
	pthread_mutex_unlock(&phil->table->start_lock);
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
		// flags_up(phil, phil->table) == false
	}
	return (NULL);
}


bool	monitor(t_table *table)
{
	int	i;
	// unsigned long long	ts;
	int	state;

	i = 0;
	pthread_mutex_lock(&table->start_lock);
	pthread_mutex_unlock(&table->start_lock);
	while (table->phil[i])
	{
		state = is_dead(table->phil[i], table);
		// printf("%i\n", state);
		if (state == 1)
		{
			// ts = get_time() - table->sim_start_time;
			print_status("died\n", table->phil[i]);
			return (false);
		}
		else if (state == 2)
			return (false);
		// if (table->meal_count > 0)
		// {
		// 	if (all_meals_eaten(table->phil[i], table) == true)
		// 		return (false);
		// }
		else
		{
			i++;
			usleep(5);
		}
	}
	return (true);
}
