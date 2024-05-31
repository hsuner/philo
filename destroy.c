/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:11:59 by hsuner            #+#    #+#             */
/*   Updated: 2024/02/08 19:20:23 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	free_malloc(t_program *x)
{
	return (free(x->mutex.fork_m), free(x->philo), 1);
}

int	init_error_fork(t_program *x, int idx)
{
	while (--idx)
		pthread_mutex_destroy(&x->mutex.fork_m[idx]);
	pthread_mutex_destroy(&x->mutex.print_m);
	pthread_mutex_destroy(&x->mutex.ctrl_m);
	pthread_mutex_destroy(&x->die.die_m);
	return (free_malloc(x));
}

int	create_error_fork(t_program *x, int idx)
{
	x->die.is_die = 1;
	while (--idx)
		pthread_join(x->philo[idx].thread, (void *)0);
	return (destroy(x));
}

int	destroy(t_program *x)
{
	unsigned char	idx;

	idx = -1;
	while (++idx < x->rl.nop)
		pthread_mutex_destroy(&x->mutex.fork_m[idx]);
	pthread_mutex_destroy(&x->mutex.print_m);
	pthread_mutex_destroy(&x->mutex.ctrl_m);
	pthread_mutex_destroy(&x->die.die_m);
	return (free_malloc(x));
}

int	finish_destroy(t_program *x)
{
	unsigned char	idx;

	idx = -1;
	while (++idx < x->rl.nop)
		pthread_join(x->philo[idx].thread, NULL);
	pthread_join(x->die.die_t, NULL);
	if (x->die.is_die && x->others.finished)
		printf(DIE, x->die.die_time, x->die.is_die);
	return (destroy(x) - 1);
}
