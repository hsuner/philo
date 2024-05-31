/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:05:08 by hsuner            #+#    #+#             */
/*   Updated: 2024/02/11 18:34:05 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, (void *)0) == -1)
		return (1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	instant_time(t_program *x)
{
	return (get_time() - x->others.start_time);
}

void	impr_usl(u_int64_t time)
{
	uint64_t	wake_up;

	wake_up = get_time() + time;
	while (get_time() < wake_up)
		usleep(100);
}

int	check_eat(t_program *x)
{
	unsigned char	i;

	if (x->rl.eat_limit)
	{
		i = -1;
		while (++i < x->rl.nop)
		{
			pthread_mutex_lock(&x->mutex.ctrl_2_m);
			if (x->philo[i].num_of_eat >= x->rl.eat_limit)
				x->others.ctrl_eat_limit++;
			pthread_mutex_unlock(&x->mutex.ctrl_2_m);
		}
		if (x->others.ctrl_eat_limit >= x->rl.nop)
		{
			pthread_mutex_lock(&x->die.die_m);
			x->others.finished = 1;
			pthread_mutex_unlock(&x->die.die_m);
			return (1);
		}
	}
	return (0);
}

int	calc_dif(t_data *data, int init_v, int sub_v, int third_v)
{
	int	result;

	result = 0;
	if (data->first_call)
	{
		result = init_v - sub_v;
		data->first_call = 0;
		data->previous_difference = result;
	}
	else
		result = init_v - third_v;
	if (result < 0)
		result = 0;
	return (result);
}
