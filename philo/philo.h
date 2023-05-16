/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:19:47 by jhusso            #+#    #+#             */
/*   Updated: 2023/05/16 10:35:24 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h> // exit atoi
# include <time.h>
# include <stdio.h> // HOXHOXHOX

typedef struct s_philo
{
	unsigned int	phil_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	meal_count;
} t_philo;

typedef struct s_th
{
	pthread_t		p;
	pthread_mutex_t	mutex;
} t_th;


// main.c
int	check_args(int ac, char **av);
int	get_args(char ** av);

// utils.c
int	ft_atoi(const char *nptr);
#endif
