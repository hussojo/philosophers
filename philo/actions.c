/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/11 12:24:36 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sleeping(t_phil *phil)
{
	if (!print_status("is sleeping", phil))
		return (0);
	ft_sleep(phil->table->time_to_sleep, phil);
	if (!print_status("is thinking", phil))
		return (0);
	return (1);
}

static int	take_forks(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->fork_lock[phil->id - 1]);
	if (!print_status("has taken the fork", phil))
		return (0);
	pthread_mutex_lock(&phil->table->fork_lock[(phil->id) \
		% phil->table->phil_count]);
	if (!print_status("has taken the fork", phil))
	{
		pthread_mutex_unlock(&phil->table->fork_lock[phil->id - 1]);
		return (0);
	}
	return (1);
}

static int	eating(t_phil *phil)
{
	if (!take_forks(phil))
		return (0);
	if (!print_status("is eating", phil))
	{
		pthread_mutex_unlock(&phil->table->fork_lock[phil->id - 1]);
		pthread_mutex_unlock(&phil->table->fork_lock[(phil->id) \
			% phil->table->phil_count]);
		return (0);
	}
	pthread_mutex_lock(&phil->meal_lock);
	phil->last_time_eat = get_time();
	pthread_mutex_unlock(&phil->meal_lock);
	ft_sleep(phil->table->time_to_eat, phil);
	update_meals(phil);
	pthread_mutex_unlock(&phil->table->fork_lock[(phil->id) \
		% phil->table->phil_count]);
	pthread_mutex_unlock(&phil->table->fork_lock[phil->id - 1]);
	return (1);
}

static int	lonely_phil(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->fork_lock[phil->id - 1]);
	if (!print_status("has taken a fork", phil))
		return (0);
	ft_sleep(phil->table->time_to_die, phil);
	return (0);
}

void	*routine(void *data)
{
	t_phil	*phil;

	phil = (t_phil *)data;
	pthread_mutex_lock(&phil->table->start_lock);
	pthread_mutex_unlock(&phil->table->start_lock);
	if (phil->table->phil_count == 1)
	{
		if (!lonely_phil(phil))
			return (NULL);
	}
	if ((phil->id % 2) == 0)
	{
		print_status("is thinking", phil);
		ft_sleep(50, phil);
	}
	while (1)
	{
		if (!eating(phil))
			break ;
		if (!sleeping(phil))
			break ;
	}
	return (NULL);
}
