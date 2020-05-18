/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_bf_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 05:37:16 by scoron            #+#    #+#             */
/*   Updated: 2020/05/18 05:57:00 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		lm_init_costs(t_node **nodes)
{
	int		i;

	i = 1;
	while (nodes[i])
	{
		nodes[i]->prev_id = -1;
		if (nodes[i]->passed)
		{
			nodes[i]->next->prev_id = -1;
			nodes[i]->next->cost = -1;
		}
		nodes[i++]->cost = -1;
	}
}

static int		lm_calc_costs(t_node *node)
{
	int			check;
	t_pipe		*pipe;

	check = 0;
	while (node && node->cost == -1)
		node = node->next;
	while (node)
	{
		pipe = node->pipes;
		while (pipe)
		{
			if (pipe->node->id != 0 && !pipe->passed &&
					(node->cost + pipe->weight < pipe->node->cost ||
											pipe->node->cost == -1))
			{
				pipe->node->cost = node->cost + pipe->weight;
				pipe->node->prev_id = node->id;
				check = 1;
			}
			pipe = pipe->next;
		}
		node = node->next;
	}
	return (check);
}

void			lm_bf_algo(t_node **nodes, int size)
{
	int			k;
	int			i;
	int			check;

	k = 1;
	lm_init_costs(nodes);
	while (k < size)
	{
		i = 0;
		check = 0;
		while (nodes[i])
		{
			if (i == LAST)
				i++;
			if (!nodes[i])
				break ;
			check += lm_calc_costs(nodes[i]);
			i++;
		}
		if (!check)
			break ;
		k++;
	}
}
