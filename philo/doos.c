/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/20 12:01:01 by jhusso           ###   ########.fr       */
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
	pthread_mutex_unlock(&phil->table->start_lock);
	time = get_time();
	print_status(1, phil, time);
	return (NULL);
}

void	print_status(int state, t_phil *phil, unsigned long long time)
{
	unsigned long long	ts;

	pthread_mutex_lock(&phil->table->print_lock);
	ts = time - phil->table->sim_start_time;
	if (state == 1)
		printf("%llu %u is thinking\n", ts, phil->id);
	if (state == 4)
		printf("%llu %u died\n", ts, phil->id);
	pthread_mutex_unlock(&phil->table->print_lock);
}

void	monitor(t_table *table)
{
	int					i;
	unsigned long long	last_meal;

	i = 0;
	while (i < table->phil_count)
	{
		last_meal = (get_time() - table->phil[i]->last_time_eat);
		if (table->time_to_die < last_meal)
		{
			print_status(4, table->phil[i], get_time());
			if (stop(table) == false)
				exit(1);
			else
				free_func(table);
		}
	}

}
