/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:09:13 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/06/23 22:18:01 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <philo_data.h>

/* init_data.c */

/*
	Converts all arguments passed by command line, allocates memory 
	for philosophers structures and mutexes, and finally configure all philosophers.
*/
void	init_data(int argc, char **argv, t_data *data);

/* utils.c */

/*
	Prints a status message with time_stamp (in ms) and philosopher number.
	if status is OFF, set status variable on data struct to OFF.
*/
void	state_message(char *message, t_philosopher *philo);

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
	Checks if a philosopher ate the meals limit and
	increments ate_meals variable if so. Also checks if all
	Philosophers ate the meals limit and returns 1 if yes, else returns 0.
*/
int		check_meals(t_philosopher *philo);

/*
	Configures all information at the philosopher structure
	indexed by the i variable.
*/
void	create_philosophers(t_data *data, int i);

#endif
