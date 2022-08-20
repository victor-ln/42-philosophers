/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:14:34 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/19 19:51:38 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static long	ft_atol(const char *nptr);
static int	ft_isspace(int c);
static int	ft_isdigit(int c);

void	init_data(int argc, char **argv, t_data *data)
{
	data->status = ON;
	data->nbr_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (data->nbr_of_philos <= 0 || data->time_to_die < 0 || \
		data->time_to_eat < 0 || data->time_to_sleep < 0)
		error(INVALID_VALUE, data);
	if (argc == 6)
	{
		data->meals_limit = ft_atol(argv[5]);
		if (data->meals_limit < 0)
			error(INVALID_VALUE, data);
	}
	data->all_forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philos);
	data->philo = malloc(sizeof(t_philosopher) * data->nbr_of_philos);
	data->tid = malloc(sizeof(pthread_t) * data->nbr_of_philos);
	if (!data->all_forks || !data->philo || !data->tid)
		error("Malloc Failed", NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->ate, NULL);
	pthread_mutex_init(&data->checker_mutex, NULL);
}

void	create_philosophers(t_data *data, int i)
{
	data->philo[i].last_meal = get_time();
	data->philo[i].number = i + 1;
	data->philo[i].forks[LEFT] = i;
	data->philo[i].forks[RIGHT] = i + 1;
	if (i + 1 == data->nbr_of_philos)
	{
		data->philo[i].forks[RIGHT] = i;
		data->philo[i].forks[LEFT] = 0;
	}
	data->philo[i].ate = 0;
	data->philo[i].data = data;
	pthread_mutex_init(data->all_forks + i, NULL);
	pthread_mutex_init(&data->philo[i].last_meal_mutex, NULL);
}

static long	ft_atol(const char *nptr)
{
	long	num;
	long	sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		num = (num * 10) + (*nptr++ - 48);
	return (num * sign);
}

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n' || \
			c == '\r' || c == '\t' || c == '\v');
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
