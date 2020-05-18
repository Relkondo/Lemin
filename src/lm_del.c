/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 05:37:36 by scoron            #+#    #+#             */
/*   Updated: 2020/05/18 06:02:59 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		lm_del(char **line, t_node *current_node, int res, int check)
{
	t_node		*tmp;

	if (res == 1)
		res = -1;
	while (current_node)
	{
		tmp = current_node->next;
		current_node->next = NULL;
		lm_del_node(&current_node);
		current_node = tmp;
	}
	if (check == 1)
		ft_strdel(line);
	return (res);
}

void	lm_del_pipes(t_pipe *current_pipe)
{
	t_pipe *tmp;

	while (current_pipe)
	{
		tmp = current_pipe->next;
		current_pipe->node = NULL;
		current_pipe->weight = 0;
		current_pipe->next = NULL;
		current_pipe->reverse = NULL;
		ft_memdel((void **)&current_pipe);
		current_pipe = tmp;
	}
}

void	lm_del_node(t_node **target)
{
	t_node	*node;

	node = *target;
	if (node->pseudo)
		ft_strdel(&(node->pseudo));
	node->cost = 0;
	node->id = 0;
	node->ants = 0;
	node->x = 0;
	node->y = 0;
	node->entry = 0;
	if (node->pipes)
		lm_del_pipes(node->pipes);
	node->pipes = NULL;
	if (node->next)
		(lm_del_node(&node->next));
	node->next = NULL;
	ft_memdel((void **)target);
}

void	lm_del_farm(t_farm *farm)
{
	int		i;
	t_node	**nodes;

	i = 0;
	nodes = farm->nodes;
	while (i < farm->size && nodes)
	{
		if (nodes[i])
		{
			lm_del_node(&(nodes[i]));
			nodes[i] = NULL;
		}
		i++;
	}
	farm->nodes = NULL;
	farm->start = 0;
	farm->end = 0;
	farm->nb_ants = 0;
	farm->size = 0;
	farm->steps = 0;
	farm->max_ways = 0;
	ft_memdel((void **)&nodes);
	ft_memdel((void **)&farm);
}

void	lm_free_ways(t_node ***ways)
{
	int		i;

	i = 0;
	while (ways[i])
		free(ways[i++]);
	free(ways);
}
