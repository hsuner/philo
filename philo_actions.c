/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:05:32 by hsuner            #+#    #+#             */
/*   Updated: 2024/02/11 16:18:09 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	p_fork(t_philo *philo, char *fork)
{
	pthread_mutex_lock(&philo->x->mutex.ctrl_m);
	pthread_mutex_lock(&philo->x->die.die_m);
	if (!philo->x->die.is_die)
	{
		pthread_mutex_unlock(&philo->x->die.die_m);
		pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
		pthread_mutex_lock(&philo->x->mutex.print_m);
		printf(FORK, instant_time(philo->x), philo->id, fork);
		pthread_mutex_unlock(&philo->x->mutex.print_m);
		return ;
	}
	pthread_mutex_unlock(&philo->x->die.die_m);
	pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
}

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->x->mutex.ctrl_m);
	pthread_mutex_lock(&philo->x->die.die_m);
	if (!philo->x->die.is_die)
	{
		pthread_mutex_unlock(&philo->x->die.die_m);
		pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
		pthread_mutex_lock(&philo->x->mutex.print_m);
		printf(EAT, instant_time(philo->x), philo->id);
		pthread_mutex_unlock(&philo->x->mutex.print_m);
		impr_usl(philo->x->rl.tte);
		pthread_mutex_lock(&philo->x->mutex.ctrl_m);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
		pthread_mutex_lock(&philo->x->mutex.ctrl_2_m);
		philo->num_of_eat++;
		pthread_mutex_unlock(&philo->x->mutex.ctrl_2_m);
		return ;
	}
	pthread_mutex_unlock(&philo->x->die.die_m);
	pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
}

void	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->x->mutex.ctrl_m);
	pthread_mutex_lock(&philo->x->die.die_m);
	if (!philo->x->die.is_die)
	{
		pthread_mutex_unlock(&philo->x->die.die_m);
		pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
		pthread_mutex_lock(&philo->x->mutex.print_m);
		printf(SLEEP, instant_time(philo->x), philo->id);
		pthread_mutex_unlock(&philo->x->mutex.print_m);
		impr_usl(philo->x->rl.tts);
		return ;
	}
	pthread_mutex_unlock(&philo->x->die.die_m);
	pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
}

void	p_think(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->x->mutex.ctrl_m);
	pthread_mutex_lock(&philo->x->die.die_m);
	if (!philo->x->die.is_die)
	{
		pthread_mutex_unlock(&philo->x->die.die_m);
		pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
		pthread_mutex_lock(&philo->x->mutex.print_m);
		printf(THINK, instant_time(philo->x), philo->id);
		pthread_mutex_unlock(&philo->x->mutex.print_m);
		if (philo->x->rl.nop == 1)
			impr_usl(philo->x->rl.ttd - philo->x->rl.tte);
		else if (philo->id == philo->x->rl.nop && philo->x->rl.nop % 2 == 1)
			impr_usl(calc_dif(data, philo->x->rl.ttd, \
				(3 * philo->x->rl.tte), (philo->x->rl.tte) + philo->x->rl.tts));
		else if (philo->id % 2 == 1)
			impr_usl(calc_dif(data, philo->x->rl.ttd, \
				philo->x->rl.tte, (philo->x->rl.tte) + philo->x->rl.tts));
		else
			impr_usl(calc_dif(data, philo->x->rl.ttd, (2 * \
				philo->x->rl.tte), (philo->x->rl.tte) + philo->x->rl.tts));
		return ;
	}
	pthread_mutex_unlock(&philo->x->die.die_m);
	pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
}
