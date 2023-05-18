/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:21:00 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/18 11:31:49 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_onlydig(char *c)
{
	while (*c)
	{
		if(*c < '0' || *c > '9')
			return (1);
		c++;
	}
	return (0);
}

int	check_args(int ac, char **av) // returns 0 if true = no problems, 1 if false = invalid params
{
	int	i;
	int	j;

	i = 1;
	// printf("ac: %i\n", ac);
	while (i < ac)
	{
		if (ft_onlydig(av[i]))
			return (1);
		if (!ft_atoi(av[i]))
			return (1);
		i++;
	}
	return (0);
}
