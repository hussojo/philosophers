/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 08:31:59 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/11 08:23:50 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_onlydig(char *c)
{
	while (*c)
	{
		if (*c < '0' || *c > '9')
			return (false);
		c++;
	}
	return (true);
}

bool	valid_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_onlydig(av[i]) == false)
			return (false);
		if (!ft_unsigned_atoi(av[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_unsigned_atoi(const char *nptr)
{
	long	res;

	res = 0;
	if (*nptr == '-')
		return (0);
	if (*nptr == '+')
		nptr++;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13) || *nptr == 48)
	{
		if (*nptr++ == '\0')
			return (0);
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr++ - '0';
		if (res > 2147483647)
			return (0);
	}
	return (res);
}
