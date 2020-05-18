/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 05:37:47 by scoron            #+#    #+#             */
/*   Updated: 2020/05/18 05:47:04 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				lm_solve_one_step(char *end, int ants)
{
	int		id;

	id = 1;
	while (id <= ants)
		ft_printf("L%d-%s ", id++, end);
	ft_printf("\n");
	return (1);
}

static void		lm_first_moves(t_farm *farm, t_node ***ways, int i, int lines)
{
	static int	id = 1;
	t_node		*orig;
	int			max;

	max = farm->steps;
	orig = farm->nodes[FIRST];
	if (farm->steps > (double)(int)farm->steps)
		lines--;
	if (ways[i][0]->cost + lines < max && id <= orig->ants)
	{
		ft_printf("L%d-%s ", id, ways[i][0]->pseudo);
		ways[i][0]->ants = id++;
	}
	else
		ways[i][0]->ants = 0;
}

static void		lm_one_move(t_node **way, t_node *end, int j)
{
	while (j > 0)
	{
		if (way[j] == end)
		{
			ft_printf("L%d-%s ", way[j - 1]->ants, way[j]->pseudo);
			end->ants--;
		}
		else
		{
			if (way[j - 1]->ants)
				ft_printf("L%d-%s ", way[j - 1]->ants, way[j]->pseudo);
			way[j]->ants = way[j - 1]->ants;
		}
		j--;
	}
}

static int		lm_first_ant_pos(t_node **way)
{
	int		j;

	j = way[0]->cost;
	while (j > 0 && !way[j - 1]->ants)
		j--;
	return (j);
}

void			lm_move(t_farm *farm, t_node ***ways, t_node **nodes)
{
	int		i;
	int		j;
	int		lines;

	i = 0;
	lines = 0;
	while (ways[i])
	{
		j = lm_first_ant_pos(ways[i]);
		lm_one_move(ways[i], nodes[LAST], j);
		lm_first_moves(farm, ways, i, lines);
		if (!ways[++i] && nodes[LAST]->ants)
		{
			i = 0;
			lines++;
			ft_printf("\n");
		}
	}
	ft_printf("\n");
}
