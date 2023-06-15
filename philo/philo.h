/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:47 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/11 11:46:33 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h> // pthread_funcs
# include <stdbool.h> // boolean
# include <sys/time.h> // gettimeofday
# include <unistd.h> // usleep
# include <stdlib.h> // free
# include <stdio.h> // printf

typedef struct s_phil	t_phil;

typedef struct s_table
{
	unsigned int		phil_count;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					meal_count;
	size_t				sim_start_time;
	unsigned int		stop_flag;
	unsigned int		all_meals_eaten;
	unsigned int		meal_flag;
	t_phil				*phil;
	pthread_mutex_t		start_lock;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		table_lock;
	pthread_mutex_t		*fork_lock;
}						t_table;

typedef struct s_phil
{
	pthread_t			p;
	unsigned int		id;
	unsigned int		meals_eaten;
	size_t				last_time_eat;
	pthread_mutex_t		meal_lock;
	t_table				*table;
}						t_phil;

// actions.c
static int		sleeping(t_phil *phil);
static int		take_forks(t_phil *phil);
static int		eating(t_phil *phil);
static int		lonely_phil(t_phil *phil);
void			*routine(void *data);

// action_utils.c
int				print_status(char *state, t_phil *phil);
void			update_meals(t_phil *phil);

// free.c
void			destroy_func(t_table *table);
void			free_func(t_table *table);

// init.c
static bool		init_forks(t_table *table);
static bool		init_mutex(t_table *table);
static bool		init_phil(t_table *table);
static bool		init_args(t_table *table, char **av);
bool			init_table(int ac, char **av, t_table *table);

// main.c
static bool		stop(t_table *table);
static bool		start(t_table *table);

// monitoring.c
static bool		is_dead(t_phil *phil, t_table *table);
bool			flags_up(t_table *table, int flag);
bool			monitor(t_table *table);
size_t			get_time(void);
void			ft_sleep(size_t ms, t_phil *phil);

// parsing.c
static bool		is_onlydig(char *c);
bool			valid_args(int ac, char **av);
int				ft_unsigned_atoi(const char *nptr);

#endif
