/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_sb_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 05:37:58 by scoron            #+#    #+#             */
/*   Updated: 2020/05/28 01:14:28 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static long	lm_total_len_ways(t_node ***ways)
{
	int		i;
	int		j;
	long	len;

	len = 0;
	i = 0;
	while (ways[i])
	{
		j = 0;
		while (ways[i][j])
		{
			j++;
			len++;
		}
		i++;
	}
	return (len);
}

double		lm_max_steps(t_farm *farm, t_node ***ways, int nb_ways)
{
	double		max;
	long		tmp;

	tmp = (long)farm->nb_ants;
	tmp = tmp + lm_total_len_ways(ways);
	max = ((double)tmp / (double)nb_ways) - (double)1;
	return (max);
}

static int	lm_reload_ways(t_farm *farm, t_node **nodes,
								t_node ****ways, int nb)
{
	t_node		***tmp;
	double		max_steps;

	if (!(tmp = lm_collect_ways(nodes, nb)))
		return (-1);
	if (farm->steps > (max_steps = lm_max_steps(farm, tmp, nb)) ||
											farm->steps == -1)
	{
		if (*ways)
			lm_free_ways(*ways);
		farm->steps = max_steps;
		*ways = tmp;
		return (1);
	}
	lm_free_ways(tmp);
	return (0);
}

int			lm_sb_algo(t_farm *farm, t_node **nodes)
{
	t_node		***ways;
	int			nb_ways;
	int			res;

	nb_ways = 1;
	ways = NULL;
	while (nb_ways < farm->max_ways + 1)
	{
		lm_bf_algo(nodes, farm->size);
		if (!lm_use_way(nodes))
			break ;
		if ((res = lm_reload_ways(farm, nodes, &ways, nb_ways)) != 1)
		{
			if (!res)
				break ;
			return (res);
		}
		nb_ways++;
	}
	if (!ways)
		return (0);
	lm_recalc_costs(ways);
	lm_move(farm, ways, nodes);
	lm_free_ways(ways);
	return (1);
}
