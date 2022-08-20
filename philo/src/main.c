/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:24:50 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/19 19:57:49 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	start_program(t_data *data);
static void	eating(t_philosopher *p);
static void	*admin(void *ptr);
static void	*loop(void *ptr);

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		error(INVALID_ARGV, NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		error("Malloc Failed", data);
	memset(data, 0, sizeof(t_data));
	init_data(argc, argv, data);
	start_program(data);
	end_program(data);
	return (0);
}

/*
	Creates each Philosopher thread and an administrator thread.
*/
static void	start_program(t_data *data)
{
	int		i;

	i = 0;
	data->init = get_time();
	while (i < data->nbr_of_philos)
		create_philosophers(data, i++);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_create(data->tid + i, NULL, &loop, data->philo + i))
			error("Thread couldn't be created", data);
		i++;
	}
	if (pthread_create(&data->admin, NULL, &admin, data))
		error("Thread couldn't be created", data);
}

/*
	The routine that each philosopher thread runs.
*/
static void	*loop(void *ptr)
{
	t_philosopher	*philo;

	philo = ptr;
	if (philo->data->nbr_of_philos == 1)
	{
		pthread_mutex_lock(philo->data->all_forks + philo->forks[LEFT]);
		state_message("has taken a fork", philo);
		pthread_mutex_unlock(philo->data->all_forks + philo->forks[LEFT]);
		return (NULL);
	}
	while (1)
	{
		if (philo->number % 2 == 0)
			usleep(1000);
		eating(philo);
		state_message("is sleeping", philo);
		usleep(philo->data->time_to_sleep);
		state_message("is thinking", philo);
		pthread_mutex_lock(&philo->data->checker_mutex);
		if (!philo->data->status)
		{
			pthread_mutex_unlock(&philo->data->checker_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->checker_mutex);
	}
	return (NULL);
}

static void	eating(t_philosopher *p)
{
	pthread_mutex_lock(p->data->all_forks + p->forks[LEFT]);
	pthread_mutex_lock(p->data->all_forks + p->forks[RIGHT]);
	state_message("has taken a fork", p);
	state_message("has taken a fork", p);
	state_message("is eating", p);
	pthread_mutex_lock(&p->last_meal_mutex);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->last_meal_mutex);
	usleep(p->data->time_to_eat);
	pthread_mutex_unlock(p->data->all_forks + p->forks[LEFT]);
	pthread_mutex_unlock(p->data->all_forks + p->forks[RIGHT]);
	pthread_mutex_lock(&p->data->ate);
	p->ate++;
	p->ate_checker = 1;
	pthread_mutex_unlock(&p->data->ate);
}

/*
	Routine that administrator thread runs, checking if any philosopher died or if
	all of them ate enough.
*/
static void	*admin(void *ptr)
{
	int		i;
	long	time;
	t_data	*data;

	data = ptr;
	while (1)
	{
		i = -1;
		while (++i < data->nbr_of_philos)
		{
			time = get_time();
			pthread_mutex_lock(&data->philo[i].last_meal_mutex);
			if (time - data->philo[i].last_meal > data->time_to_die)
			{
				pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
				pthread_mutex_lock(&data->checker_mutex);
				data->status = OFF;
				pthread_mutex_unlock(&data->checker_mutex);
				pthread_mutex_lock(&data->print);
				printf("%ld %d is dead\n", (get_time() - data->init), i + 1);
				pthread_mutex_unlock(&data->print);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			if (data->meals_limit && check_meals(data->philo + i))
				return (NULL);
			usleep(700);
		}
	}
}
