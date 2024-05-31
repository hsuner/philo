/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_conf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:11:52 by hsuner            #+#    #+#             */
/*   Updated: 2024/02/11 16:19:10 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	create_rl(int ac, char **av, t_program *x)
{
	x->rl.nop = ft_atoi(av[1]);
	x->rl.ttd = ft_atoi(av[2]);
	x->rl.tte = ft_atoi(av[3]);
	x->rl.tts = ft_atoi(av[4]);
	if (ac == 6)
		x->rl.eat_limit = ft_atoi(av[5]);
	else
		x->rl.eat_limit = 0;
	return (0);
}

int	alloc_philo(t_program *x)
{
	x->mutex.fork_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* x->rl.nop);
	if (!x->mutex.fork_m)
		return (printf(FORK_CREATE_ERR), 1);
	x->philo = (t_philo *)malloc(sizeof(t_philo) * x->rl.nop);
	if (!x->philo)
		return (printf(PHILO_CREATE_ERR), free(x->mutex.fork_m), 1);
	return (0);
}

static	int	mutex_init(t_program *x)
{
	if (pthread_mutex_init(&x->mutex.print_m, (void *)0))
		return (printf(MUTEX_INIT_ERR), free_malloc(x));
	if (pthread_mutex_init(&x->mutex.ctrl_m, (void *)0))
	{
		pthread_mutex_destroy(&x->mutex.print_m);
		return (printf(MUTEX_INIT_ERR), free_malloc(x));
	}
	if (pthread_mutex_init(&x->mutex.ctrl_2_m, (void *)0))
	{
		pthread_mutex_destroy(&x->mutex.print_m);
		pthread_mutex_destroy(&x->mutex.ctrl_m);
		return (printf(MUTEX_INIT_ERR), free_malloc(x));
	}
	if (pthread_mutex_init(&x->die.die_m, (void *)0))
	{
		pthread_mutex_destroy(&x->mutex.print_m);
		pthread_mutex_destroy(&x->mutex.ctrl_m);
		pthread_mutex_destroy(&x->mutex.ctrl_2_m);
		return (printf(MUTEX_INIT_ERR), free_malloc(x));
	}
	return (0);
}

int	philo_init(t_program *x)
{
	unsigned int	i;

	i = -1;
	if (mutex_init(x))
		return (1);
	while (++i < x->rl.nop)
	{
		x->philo[i].id = i + 1;
		x->philo[i].l_fork = i;
		if (!i)
			x->philo[i].r_fork = x->rl.nop - 1;
		else
			x->philo[i].r_fork = i - 1;
		x->philo[i].num_of_eat = 0;
		x->philo[i].last_eat = get_time();
		x->philo[i].x = x;
		if (pthread_mutex_init(&x->mutex.fork_m[i], (void *)0))
			return (printf(MUTEX_INIT_ERR), init_error_fork(x, i));
	}
	return (0);
}

int	run_simulation(t_program *x)
{
	unsigned char	i;

	i = -1;
	x->die.is_die = 0;
	x->others.ctrl_eat_limit = 0;
	x->others.finished = 0;
	x->others.start_time = get_time();
	while (++i < x->rl.nop)
	{
		if (pthread_create(&x->philo[i].thread, (void *)0, life,
				(void *)&x->philo[i]))
			return (create_error_fork(x, i));
	}
	if (pthread_create(&x->die.die_t, (void *)0, die, (void *)x))
		return (printf(MUTEX_CREATE_ERR), destroy(x));
	return (finish_destroy(x));
}
