/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:41:35 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/28 16:12:39 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int state, t_phil *phil)
{
	unsigned long long	ts;

	pthread_mutex_lock(&phil->table->print_lock);
	ts = get_time() - phil->table->sim_start_time;
	if (state == 1)
		printf("\e[31m %llu %u is thinking\n", ts, phil->id);
	else if (state == 2)
		printf("\e[32m %llu %u is eating\n", ts, phil->id);
	else if (state == 3)
		printf("\e[35m %llu %u is sleeping\n", ts, phil->id);
	else if (state == 4)
	{
		printf("\e[31m %llu %u died???\n", ts, phil->id);
		stop(phil->table);
	}
	else if (state == 5)
		printf("\e[36m %llu %u has taken a right fork\n", ts, phil->id);
	else if (state == 6)
		printf("\e[36m %llu %u has taken a left fork\n", ts, phil->id);
	pthread_mutex_unlock(&phil->table->print_lock);
	pthread_mutex_lock(&phil->table->maintenance);
	if (flags_up(phil, phil->table) == true)
		stop(phil->table);
	pthread_mutex_unlock(&phil->table->maintenance);
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
		pthread_mutex_lock(&phil->table->maintenance);
		if (flags_up(phil, phil->table) == true)
			stop(phil->table);
		pthread_mutex_unlock(&phil->table->maintenance);
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
