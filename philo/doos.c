/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/20 09:09:58 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*think(void *data)
{
	t_phil				*phil;
	unsigned long long	time;

	phil = (t_phil *)data;
	// printf("Phil nro %i was here\n", phil->id);
	pthread_mutex_lock(&phil->table->start_lock);
	time = get_time();
	print_status(1, phil, time);
	pthread_mutex_unlock(&phil->table->start_lock);
	return (NULL);
}
void	print_status(int state, t_phil *phil, unsigned long long time)
{
	unsigned long long	ts;

	pthread_mutex_lock(&phil->table->print_lock);
	ts = time - phil->table->sim_start_time;
	if (state == 1)
		printf("%llu %u is thinking\n", ts, phil->id);
	pthread_mutex_unlock(&phil->table->print_lock);
}
