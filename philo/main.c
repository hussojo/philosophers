/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/31 15:38:35 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop(t_table *table)
{
	int					i;
	unsigned long long	ts;

	i = 0;
	pthread_mutex_lock(&table->print_lock);
	if (table->dead_id > 0)
	{
		ts = get_time() - table->sim_start_time;
		printf("\e[31m %llu %i died\n", ts, table->dead_id);
	}
	pthread_mutex_unlock(&table->print_lock);
	pthread_mutex_destroy(&table->maintenance);
	pthread_mutex_destroy(&table->start_lock);
	pthread_mutex_destroy(&table->print_lock);
	i = 0;
	while (i < table->phil_count)
	{
		pthread_mutex_destroy(table->fork_lock);
		i++;
	}
	exit(0);
}

static bool	start(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->start_lock);
	while (i < table->phil_count)
	{
		if (pthread_create(&table->phil[i]->p, NULL, &routine, table->phil[i]))
			return (false);
		i++;
	}
	pthread_mutex_unlock(&table->start_lock);
	return (true);
}

int	main(int ac, char **av)
{
	t_phil				*phil;
	t_table				*table;
	unsigned int		start_time;
	unsigned long long	ts;

	if (ac < 5 || ac > 6)
		exit (1);
	if (valid_args(ac, av) == false)
		exit (1);
	table = init_table(ac, av);
	if (!table)
		exit (1);
	start(table);
	while (42)
	{
		if (monitor(table) == false)
			stop(table);
	}
	return (0);
}
