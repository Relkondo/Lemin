/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_collect_ways.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 05:37:32 by scoron            #+#    #+#             */
/*   Updated: 2020/05/18 05:46:27 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_node	**lm_save_way(t_node **nodes, t_node **way, t_node *node)
{
	t_pipe		*pipe;
	t_pipe		*tmp;
	int			j;

	j = 0;
	pipe = node->pipes;
	if (node->id != LAST)
		way[j++] = node;
	while (node->id != LAST && pipe->node != nodes[LAST])
	{
		if (pipe->passed && !pipe->reverse->passed)
		{
			way[j++] = pipe->node;
			tmp = pipe;
			pipe = pipe->node->pipes;
		}
		else
			pipe = pipe->next;
		if (!pipe)
			pipe = nodes[-tmp->node->id]->pipes;
	}
	way[j++] = nodes[LAST];
	way[j] = NULL;
	return (way);
}

static int		lm_calc_len(t_node **nodes, t_node *node, t_node *goal)
{
	t_pipe		*pipe;
	t_pipe		*tmp;
	int			len;

	len = 1;
	pipe = node->pipes;
	if (node == goal)
		return (len);
	while (pipe->node != goal)
	{
		if (pipe->passed && !pipe->reverse->passed)
		{
			len++;
			tmp = pipe;
			pipe = pipe->node->pipes;
		}
		else
			pipe = pipe->next;
		if (!pipe)
			pipe = nodes[-tmp->node->id]->pipes;
	}
	return (len + 1);
}

static t_node	**lm_get_way(t_node **nodes, t_node *node)
{
	t_node		**new_way;
	int			w_len;

	w_len = lm_calc_len(nodes, node, nodes[LAST]) + 1;
	if (!(new_way = ft_memalloc(sizeof(t_node *) * w_len)))
		return (NULL);
	new_way[w_len - 1] = NULL;
	new_way[0] = node;
	new_way = lm_save_way(nodes, new_way, node);
	return (new_way);
}

t_node			***lm_collect_ways(t_node **nodes, int nb_ways)
{
	t_pipe		*pipe;
	t_node		***ways;
	int			i;

	i = 0;
	if (!(ways = ft_memalloc(sizeof(t_node **) * (nb_ways + 1))))
		return (NULL);
	ways[nb_ways] = NULL;
	pipe = nodes[FIRST]->pipes;
	while (pipe && i < nb_ways)
	{
		if (pipe->passed)
			if (!(ways[i++] = lm_get_way(nodes, pipe->node)))
				return (NULL);
		pipe = pipe->next;
	}
	if (lm_duplic_nodes(ways) == -1)
		return (NULL);
	return (ways);
}
