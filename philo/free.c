/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:52:32 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/02 10:25:09 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_func(t_table *table)
{
	int	i;

	i = 0;
	// printf("*****\nHERE FREE\n*****\n");
	if (!table)
		return ;
	while (i < table->phil_count && table->phil[i])
	{
		free (table->phil[i]);
		i++;
	}
	free (table->phil);
	free (table);
	// exit (0);
}
