/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:47 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/22 10:14:04 by jhusso           ###   ########.fr       */
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

// # define THINK "is thinking" 1
// # define EAT "is eating" 2
// # define SLEEP "is sleeping" 3
// # define DIE "died" 4
// # define FORK "has taken a fork" 5


typedef struct s_phil	t_phil;

typedef struct s_table
{
	unsigned int		phil_count;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		meal_count;
	unsigned long long	sim_start_time;
	unsigned int		all_eat;
	t_phil				**phil;
	// pthread_t			watcher;
	pthread_mutex_t		start_lock;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		*fork_lock;
} 						t_table;

typedef struct s_phil
{
	pthread_t			p;
	unsigned int		id;
	unsigned int		meals_eaten;
	unsigned long long	last_time_eat;
	t_table				*table;
} 						t_phil;

// main.c
bool	stop(t_table *table);
static bool	start(t_table *table);

// init.c
static bool	init_forks(t_table *table);
static bool	init_mutex(t_table *table);
t_phil		**init_phil(int ac, t_table *table);
t_table		*init_table(int ac, char **av);

// checks.c
static bool	is_onlydig(char *c);
bool		valid_args(int ac, char **av);

// utils.c
void	print_status(int state, t_phil *phil);
int		get_time(void);
void	ft_sleep(unsigned long long ms);
int		ft_atoi(const char *nptr);

// doos.c
void	sleeping(t_phil *phil);
void	eat(t_phil *phil);
void	think(t_phil *phil);
void	*routine(void *data);
void	monitor(t_table *table);

// free.c
void	free_func(t_table *table);
#endif
