/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/03 16:43:43 by jhusso           ###   ########.fr       */
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
}

static bool	start(t_table *table)
{
	int	i;


	i = 0;
	pthread_mutex_lock(&table->maintenance);
	while (i < table->phil_count)
	{
		if (pthread_create(&table->phil[i]->p, NULL, &routine, table->phil[i]))
			return (false);
		i++;
	}
	table->sim_start_time = get_time();
	pthread_mutex_unlock(&table->maintenance);
	return (true);
}

int	main(int ac, char **av)
{
	t_phil				*phil;
	t_table				*table;
	unsigned int		start_time;
	unsigned long long	ts;

	if (ac < 5 || ac > 6)
		printf("Invalid amount of arguments\n");
	if (valid_args(ac, av) == false)
		printf("Invalid arguments\n");
	table = init_table(ac, av);
	if (!table)
		return (-1);
	if (start(table) == false)
		return (-1);
	if (monitor(table) == false)
	{
		// printf("HERE IN MAIN\n");
		stop(phil, table);
		free_func(table);
	}
	return (0);
}
