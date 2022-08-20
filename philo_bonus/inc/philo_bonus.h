/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:09:38 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/06/23 21:59:13 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <philo_data_bonus.h>

/* init_data.c */

/*
	Converts all arguments passed by command line,
	allocates memory for philosophers structures and mutexes,
	and finally configure all philosophers.
*/
void	init_data(int argc, char **argv, t_data *data);

/* utils.c */

/*
	Prints a status message with time_stamp (in ms) and philosopher number.
	if status is OFF, set status variable on data struct to OFF.
*/
void	state_message(char *message, t_philosopher *p);

/*
	Prints Error\\n followed by passed message,
	calls end_program function and exits with errno status.
*/
void	error(char *message, t_data *data);

/*
	Frees all allocated memory, wait all threads return, and destroys all mutexes.
*/
void	end_program(t_data *data);

/*
	Calls gettimeofday() and converts seconds and
	milliseconds into microseconds and returns its value.
*/
long	get_time(void);

/*
*/
void	*admin(void *ptr);

/*
*/
void	*stop_admin_when_dies(void *ptr);

void	*stop_admin_at_meals_limit(void *ptr);

void	post_semaphores(sem_t *semaphore, int n);

void	unlink_semaphores(void);

#endif
