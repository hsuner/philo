/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:15:23 by hsuner            #+#    #+#             */
/*   Updated: 2024/02/09 16:18:16 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_program	x;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philos [# Philosophers] [ttd] [tte] ");
		printf("[tts] <[times_each_philosopher_must_eat]>\n");
		return (1);
	}
	if (arg_check(av))
		return (1);
	if (create_rl(ac, av, &x))
		return (1);
	if (alloc_philo(&x))
		return (1);
	if (philo_init(&x))
		return (1);
	if (run_simulation(&x))
		return (1);
	return (0);
}
