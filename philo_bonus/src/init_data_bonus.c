/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:14:34 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/06/27 21:39:57 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static long	ft_atol(const char *nptr);
static int	ft_isspace(int c);
static int	ft_isdigit(int c);

void	init_data(int argc, char **argv, t_data *data)
{
	unlink_semaphores();
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
	data->all_forks = sem_open("forks", O_CREAT, 0660, data->nbr_of_philos);
	data->print = sem_open("state_message", O_CREAT, 0666, 1);
	data->eating = sem_open("eating", O_CREAT, 0666, 1);
	data->flag = sem_open("flag", O_CREAT, 0666, 0);
	data->ate = sem_open("ate", O_CREAT, 0666, 0);
	data->philo = malloc(sizeof(t_philosopher) * data->nbr_of_philos);
	data->pid = malloc(sizeof(pid_t) * data->nbr_of_philos);
	if (!data->philo || !data->pid)
		error("Malloc failed", data);
}

void	unlink_semaphores(void)
{
	sem_unlink("state_message");
	sem_unlink("ate");
	sem_unlink("forks");
	sem_unlink("flag");
	sem_unlink("eating");
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
