/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:47 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/18 12:01:42 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h> // bool funcs
# include <sys/time.h> // gettimeofday
# include <unistd.h> // usleep
# include <stdlib.h> // exit atoi
# include <time.h>
# include <stdio.h> // HOXHOXHOX

typedef struct s_phil
{
	unsigned int		id;
	unsigned long long	last_time_eat;
} t_phil;


typedef struct s_table
{
	unsigned int	phil_count; // also fork mutex count
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	meal_count;
} t_table;

typedef struct s_th
{
	pthread_t		p;
	pthread_mutex_t	mutex;
} t_th;


// main.c
int		init_table(int ac, char **av);

// checks.c
static bool	is_onlydig(char *c);
bool		valid_args(int ac, char **av);

// utils.c
int		get_time(void);
void	ft_sleep(unsigned long long ms);
int		ft_atoi(const char *nptr);
#endif
