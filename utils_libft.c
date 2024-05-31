/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:37:17 by hsuner            #+#    #+#             */
/*   Updated: 2024/02/05 18:04:54 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	if (c == '\0')
		return (s + i);
	return (0);
}

int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	if (ft_strchr("+", *str))
		str++;
	res = 0;
	while (*str != '\0' && ft_strchr("0123456789", *str))
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (res);
}
