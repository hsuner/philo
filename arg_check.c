/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:36:45 by hsuner            #+#    #+#             */
/*   Updated: 2024/02/11 15:53:43 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	nbr_check(char *str, int id)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && (str[0] != '+'))
			return (printf(ARG_ERR), 1);
		i++;
	}
	i = ft_atoi(str);
	if (id == 1 && ((ft_atoi(str) > 200) || (ft_atoi(str) < 1)))
	{
		if (i == 0 || i == -1)
			return (printf(ARG_ERR), 1);
		else
			return (printf(PH_COUNT_ERR), 1);
	}
	else if (id != 1)
	{
		if (i == 0 || i == -1)
			return (printf(ARG_ERR), 1);
		else if (i < 60 && id != 5 && i != -1)
			return (printf(RULE_VL), 1);
	}
	return (0);
}

int	arg_check(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (nbr_check(argv[i], i))
			return (1);
	}
	return (0);
}
