/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:40:30 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/11 11:42:45 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(char *state, t_phil *phil)
{
	size_t	ts;

	pthread_mutex_lock(&phil->table->print_lock);
	if (flags_up(phil->table, 0) == false)
	{
		ts = get_time() - phil->table->sim_start_time;
		printf("%zu %u %s\n", ts, phil->id, state);
		pthread_mutex_unlock(&phil->table->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&phil->table->print_lock);
	return (0);
}

void	update_meals(t_phil *phil)
{
	pthread_mutex_lock(&phil->table->table_lock);
	phil->meals_eaten++;
	if (phil->meals_eaten >= phil->table->meal_count)
		phil->table->all_meals_eaten++;
	pthread_mutex_unlock(&phil->table->table_lock);
}
