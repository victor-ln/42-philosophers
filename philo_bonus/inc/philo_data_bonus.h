/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:00:04 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/19 20:08:09 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DATA_BONUS_H
# define PHILO_DATA_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

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
	t_data			*data;
	int				ate;
	int				number;
	long			last_meal;
	pthread_mutex_t	last_meal_mutex;
};

struct s_data {
	int				nbr_of_philos;
	long			time_to_sleep;
	long			time_to_die;
	long			time_to_eat;
	long			meals_limit;
	int				ate_meals;
	int				status;
	long			init;
	pid_t			*pid;
	pthread_t		tid[3];
	pthread_mutex_t	checker_mutex;
	sem_t			*print;
	sem_t			*ate;
	sem_t			*flag;
	sem_t			*eating;
	sem_t			*all_forks;
	t_philosopher	*philo;
};

#endif
