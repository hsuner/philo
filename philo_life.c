/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:12:47 by hsuner            #+#    #+#             */
/*   Updated: 2024/02/08 20:01:47 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*die(void *tmp_program)
{
	t_program		*x;
	unsigned char	i;

	x = (t_program *)tmp_program;
	while (!check_eat(x))
	{
		i = -1;
		while (++i < x->rl.nop)
		{
			pthread_mutex_lock(&x->mutex.ctrl_m);
			if ((get_time() - x->philo[i].last_eat) > x->rl.ttd + 2)
			{
				pthread_mutex_lock(&x->die.die_m);
				x->die.is_die = x->philo[i].id;
				x->others.finished = 1;
				pthread_mutex_unlock(&x->die.die_m);
				x->die.die_time = instant_time(x);
				pthread_mutex_unlock(&x->mutex.ctrl_m);
				return ((void *)0);
			}
			pthread_mutex_unlock(&x->mutex.ctrl_m);
		}
		impr_usl(1);
	}
	return ((void *)0);
}

static	void	data_init(t_data *data)
{
	data->first_call = 1;
	data->previous_difference = 0;
}

void	lifecycle(t_philo *philo, t_data *data)
{
	while (!philo->x->others.finished || (philo->x->rl.nop == 1))
	{
		pthread_mutex_unlock(&philo->x->die.die_m);
		p_think(philo, data);
		pthread_mutex_lock(&philo->x->mutex.fork_m[philo->l_fork]);
		p_fork(philo, "l_fork");
		if (philo->x->rl.nop == 1)
			break ;
		pthread_mutex_lock(&philo->x->mutex.fork_m[philo->r_fork]);
		p_fork(philo, "r_fork");
		p_eat(philo);
		pthread_mutex_unlock(&philo->x->mutex.fork_m[philo->l_fork]);
		pthread_mutex_unlock(&philo->x->mutex.fork_m[philo->r_fork]);
		p_sleep(philo);
		pthread_mutex_lock(&philo->x->die.die_m);
	}
	return ;
}

void	*life(void *tmp_philo)
{
	t_philo		*philo;
	t_data		data;

	philo = (t_philo *)(tmp_philo);
	data_init(&data);
	if (philo->id % 2 == 0)
		impr_usl(1);
	pthread_mutex_lock(&philo->x->die.die_m);
	lifecycle(philo, &data);
	pthread_mutex_unlock(&philo->x->die.die_m);
	return ((void *)0);
}
