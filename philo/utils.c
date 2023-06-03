/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:41:35 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/03 16:55:34 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Here we print what Phil is dosing, and one Phil enters at a time, either from monitor
("died") or routine or sleep */

int	print_status(char *state, t_phil *phil)
{
	unsigned long long	ts;

	pthread_mutex_lock(&phil->table->maintenance);
	if(is_dead(phil, phil->table))
	{
		ts = get_time() - phil->table->sim_start_time;
		printf("%llu %u %s\n", ts, phil->id, state);
	}
	else
	{
		pthread_mutex_unlock(&phil->table->maintenance);
		return (0);
	}
	pthread_mutex_unlock(&phil->table->maintenance);
	return (1);
}


int	get_time(void)
{
	struct timeval		tv;
	unsigned long long	start_time;

	if (gettimeofday(&tv, NULL) == 0)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else
		return (0);
}

void	ft_sleep(unsigned long long ms, t_phil *phil)
{
	unsigned long long	time;

	time = get_time();
	while ((get_time() - time) < ms)
	{
		usleep (100);
	}
}

int	ft_atoi(const char *nptr)
{
	int		s;
	long	res;

	s = 1;
	res = 0;
	if (*nptr == '-')
		s *= -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13) || *nptr == 48)
	{
		if (*nptr++ == '\0')
			return (0);
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr++ - '0';
		if ((res > 2147483647 && s == 1) || (res < -2147483648 && s != 1))
			return (0);
	}
	res = res * s;
	return (res);
}
