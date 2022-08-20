/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:36:28 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/20 18:28:49 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	error(char *message, t_data *data)
{
	printf("Error\n%s\n", message);
	if (data)
		end_program(data);
	exit(errno);
}

void	end_program(t_data *data)
{
	int	i;

	i = 0;
	sem_wait(data->flag);
	while (i < data->nbr_of_philos)
		kill(data->pid[i++], SIGKILL);
	sem_close(data->all_forks);
	sem_close(data->eating);
	sem_close(data->ate);
	sem_close(data->print);
	sem_close(data->flag);
	unlink_semaphores();
	free(data->philo);
	free(data->pid);
	free(data);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	state_message(char *message, t_philosopher *p)
{
	sem_wait(p->data->print);
	if (p->data->status != OFF)
		printf("%ld %d %s\n", (get_time() - p->data->init), p->number, message);
	sem_post(p->data->print);
}

void	post_semaphores(sem_t *semaphore, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		sem_post(semaphore);
		usleep(200);
		i++;
	}
}
