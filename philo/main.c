/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/03 10:56:14 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop(t_phil *phil, t_table *table)
{
	int					i;

	i = 0;
	while (i < table->phil_count)
	{
		pthread_join(table->phil[i]->p, NULL);
		i++;
	}
	i = 0;
	while (i < table->phil_count)
	{
		pthread_mutex_destroy(table->fork_lock);
		i++;
	}
	pthread_mutex_destroy(&table->maintenance);
	pthread_mutex_destroy(&table->start_lock);
	pthread_mutex_destroy(&table->print_lock);
	// exit(0);
}

static bool	start(t_table *table)
{
	int	i;


	i = 0;
	// table->sim_start_time = get_time();
	pthread_mutex_lock(&table->start_lock);
	// printf("start time: %llu\n", table->sim_start_time);
	while (i < table->phil_count)
	{
		if (pthread_create(&table->phil[i]->p, NULL, &routine, table->phil[i]))
			return (false);
		i++;
	}
	table->start_flag = 1;
	table->sim_start_time = get_time();
	pthread_mutex_unlock(&table->start_lock);
	return (true);
}

int	main(int ac, char **av)
{
	// printf("****HERE MAIN****");
	t_phil				*phil;
	t_table				*table;
	unsigned int		start_time;
	unsigned long long	ts;

	if (ac < 5 || ac > 6)
		exit (1); //
	if (valid_args(ac, av) == false)
		exit (1); //
	table = init_table(ac, av);
	if (!table)
		exit (1); //
	if (start(table) == true)
	{
		if (monitor(table) == false)
			break ;
		stop(phil, table);
	}
	free_func(table);
	return (0);
}
