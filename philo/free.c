/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:52:32 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/15 09:32:39 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_func(t_table *table)
{
	if (table->phil)
		free (table->phil);
	if (table->fork_lock)
		free (table->fork_lock);
}
