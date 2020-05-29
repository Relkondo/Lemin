/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 05:36:36 by scoron            #+#    #+#             */
/*   Updated: 2020/05/29 00:06:07 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

extern int	g_v;

static int	error_usage(void)
{
	ft_printf("USAGE : ./lem-in [-v] < some_map\n");
	ft_printf("ERROR\n");
	return (0);
}

int			lm_parse_bonus(int ac, char **av)
{
	int i;
	int j;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] != '-')
			return (error_usage());
		j = 0;
		while (av[i][++j])
		{
			if (av[i][j] == 'v' && g_v == 0)
				g_v = 1;
			else
				return (error_usage());
		}
	}
	return (1);
}

int			lm_gnl(int fd, char **line)
{
	if (g_v == 1)
		return (get_next_line(fd, line));
	else
		return (get_next_line_lm(fd, line));
}
