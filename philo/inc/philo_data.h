/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:00:04 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/19 19:39:46 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DATA_H
# define PHILO_DATA_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

# define LEFT	0
# define RIGHT	1

# define ON		1
# define OFF	0

# define INVALID_VALUE	"Invalid parameters! Philosopher must be \
non zero positive number and others must be unsigned positive numbers"
# define INVALID_ARGV	"You must specify at least 4 arguments and maximum 5 including:\n\
- number_of_philosophers,\n\
- time_to_die,\n\
- time_to_eat,\n\
- time_to_sleep,\n\
- [number_of_times_each_philosopher_must_eat] (optional)."

typedef struct s_philosopher	t_philosopher;
typedef struct s_data			t_data;

struct s_philosopher{
	int				number;
	int				ate;
	long			last_meal;
	int				ate_checker;
	int				forks[2];
	pthread_mutex_t	last_meal_mutex;
	t_data		*data;
};

struct s_data {
	int				nbr_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_limit;
	int				ate_meals;
	int				status;
	long			init;
	pthread_t		admin;
	pthread_t		*tid;
	t_philosopher	*philo;
	pthread_mutex_t	checker_mutex;
	pthread_mutex_t	*all_forks;
	pthread_mutex_t	print;
	pthread_mutex_t	ate;
};

#endif
