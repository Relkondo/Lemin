/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 11:44:17 by scoron            #+#    #+#             */
/*   Updated: 2020/05/18 05:59:23 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = 10 * result + str[i] - '0';
		i++;
	}
	return (sign * (int)result);
}

int	ft_atoi_lm(const char *str)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = (str[i++] == '-' ? -1 : 1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 214748364)
			return (0);
		if (result == 214748364 && ((sign == 1 && str[i] == '8')
											|| str[i] == '9'))
			return (0);
		result = 10 * result + str[i++] - '0';
	}
	return (sign * (int)result);
}
