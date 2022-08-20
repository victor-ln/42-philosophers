/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:24:50 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/19 19:59:55 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	create_philosopher(t_data *data, int i);
static void	start_program(t_data *data);
static void	eating(t_philosopher *p);
static void	loop(t_philosopher *p);

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

static void	start_program(t_data *d)
{
	int		i;

	i = -1;
	while (++i < d->nbr_of_philos)
	{
		d->pid[i] = fork();
		if (!d->pid[i])
		{
			sem_wait(d->flag);
			create_philosopher(d, i);
			if (pthread_create(&d->tid[0], NULL, &admin, d->philo + i))
				error("Thread couldn't be created", d);
			if (pthread_create(&d->tid[1], NULL, &stop_admin_when_dies, d))
				error("Thread couldn't be created", d);
			if (pthread_create(&d->tid[2], NULL, &stop_admin_at_meals_limit, d))
				error("Thread couldn't be created", d);
			loop(d->philo + i);
		}
	}
	i = -1;
	while (++i < d->nbr_of_philos)
		sem_post(d->flag);
	usleep(1000);
}

static void	create_philosopher(t_data *data, int i)
{
	data->philo[i].last_meal = get_time();
	data->philo[i].number = i + 1;
	data->philo[i].ate = 0;
	data->philo[i].data = data;
	data->init = get_time();
}

static void	loop(t_philosopher *p)
{
	if (p->data->nbr_of_philos == 1)
	{
		sem_wait(p->data->all_forks);
		state_message("has taken a fork", p);
		usleep((p->data->time_to_die * 1000));
		sem_post(p->data->all_forks);
		exit(0);
	}
	while (p->data->status)
	{
		usleep(1000);
		eating(p);
		state_message("is sleeping", p);
		usleep(p->data->time_to_sleep);
		state_message("is thinking", p);
	}
	exit(0);
}

static void	eating(t_philosopher *p)
{
	sem_wait(p->data->all_forks);
	sem_wait(p->data->all_forks);
	state_message("has taken a fork", p);
	state_message("has taken a fork", p);
	state_message("is eating", p);
	p->last_meal = get_time();
	usleep(p->data->time_to_eat);
	p->ate++;
	sem_post(p->data->all_forks);
	sem_post(p->data->all_forks);
}
