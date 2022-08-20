/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:43:11 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/20 18:24:24 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	*admin(void *ptr)
{
	long			time;
	t_philosopher	*p;

	p = ptr;
	while (1)
	{
		time = get_time();
		if (time - p->last_meal > p->data->time_to_die)
		{
			sem_wait(p->data->print);
			p->data->status = OFF;
			printf("%ld %d is dead\n", (time - p->data->init), p->number);
			post_semaphores(p->data->flag, p->data->nbr_of_philos);
			sem_post(p->data->print);
			return (NULL);
		}
		if (p->data->meals_limit == p->ate && p->data->meals_limit)
			post_semaphores(p->data->ate, p->data->nbr_of_philos);
		usleep(700);
	}
	return (NULL);
}

void	*stop_admin_when_dies(void *ptr)
{
	t_data	*data;

	data = ptr;
	sem_wait(data->flag);
	sem_post(data->flag);
	data->status = OFF;
	return (NULL);
}

void	*stop_admin_at_meals_limit(void *ptr)
{
	t_data	*data;
	int		i;

	data = ptr;
	i = 0;
	if (!data->meals_limit || data->nbr_of_philos == 1)
		return (NULL);
	while (i < data->nbr_of_philos)
	{
		sem_wait(data->ate);
		usleep(200);
		i++;
	}
	data->status = OFF;
	usleep(1000);
	sem_post(data->flag);
	return (NULL);
}
