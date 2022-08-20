/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:36:28 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/19 19:48:12 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	error(char *message, t_data *data)
{
	printf("Error\n%s\n", message);
	if (data)
	{
		end_program(data);
		free(data);
	}
	exit(errno);
}

void	end_program(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo)
	{
		pthread_join(data->admin, NULL);
		while (i < data->nbr_of_philos)
			pthread_join(data->tid[i++], NULL);
		free(data->philo);
		free(data->tid);
	}
	i = 0;
	if (data->all_forks)
	{
		while (i < data->nbr_of_philos)
		{
			pthread_mutex_destroy(data->all_forks + i++);
			pthread_mutex_destroy(&data->philo[i].last_meal_mutex);
		}
		free(data->all_forks);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->ate);
	pthread_mutex_destroy(&data->checker_mutex);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	state_message(char *message, t_philosopher *p)
{
	pthread_mutex_lock(&p->data->print);
	pthread_mutex_lock(&p->data->checker_mutex);
	if (p->data->status != OFF)
		printf("%ld %d %s\n", (get_time() - p->data->init), p->number, message);
	pthread_mutex_unlock(&p->data->checker_mutex);
	pthread_mutex_unlock(&p->data->print);
}

int	check_meals(t_philosopher *p)
{
	pthread_mutex_lock(&p->data->ate);
	if (p->data->meals_limit == p->ate && p->ate_checker)
	{
		p->data->ate_meals++;
		pthread_mutex_lock(&p->data->checker_mutex);
		p->ate_checker = 0;
		pthread_mutex_unlock(&p->data->checker_mutex);
	}
	pthread_mutex_unlock(&p->data->ate);
	if (p->data->ate_meals == p->data->nbr_of_philos)
	{
		p->data->status = OFF;
		return (1);
	}
	return (0);
}
