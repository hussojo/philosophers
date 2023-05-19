/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:12:45 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/19 08:55:50 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*think(void *data)
{
	t_phil	*phil;
	phil = (t_phil *)data;

	// pthread_mutex_init(&phil->table->start_lock, NULL);
	pthread_mutex_lock(&phil->table->start_lock);
	printf("phil no. %i thinkin\n", phil->id);
	pthread_mutex_unlock(&phil->table->start_lock);
	return (0);
}

void	*monitor(void *data)
{
	t_phil	*phil;
	phil = (t_phil *)data;

	pthread_mutex_lock(&phil->table->start_lock);
	printf("watcher monitoring\n");
	pthread_mutex_unlock(&phil->table->start_lock);
	return (0);
}