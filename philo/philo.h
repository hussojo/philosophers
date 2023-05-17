/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:47 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/17 11:42:11 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h> // exit atoi
# include <time.h>
# include <stdio.h> // HOXHOXHOX

typedef struct s_phil
{
	unsigned int	id;
	unsigned int	last_time_eat;
} t_phil;


typedef struct s_args
{
	unsigned int	phil_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	meal_count;
} t_args;

typedef struct s_th
{
	pthread_t		p;
	pthread_mutex_t	mutex;
} t_th;


// main.c
int		check_args(int ac, char **av);
int		get_args(char **av, t_args *args);
void	init_phil(t_phil *phil, int start_time);

// utils.c
int	ft_atoi(const char *nptr);
#endif
