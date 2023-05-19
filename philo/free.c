/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:52:32 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/19 13:02:42 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_func(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->phil_count)
	{
		free (table->phil[i]);
		i++;
	}
	free (table->phil);
	free (table);
}
