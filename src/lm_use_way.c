#include "lemin.h"

static int		lm_verif_prev(t_node **nodes, int prev_id)
{
	if (prev_id == -1 || (prev_id >= 0 && !nodes[prev_id]) ||
		(prev_id < 0 && !nodes[-prev_id]->next))
		return (0);
	return (1);
}

static t_node	*lm_find_prev(t_node **nodes, t_node *node)
{
	if (node->prev_id == -1)
		return (NULL);
	if (node->prev_id >= 0)
		return (nodes[node->prev_id]);
	else
		return (nodes[-node->prev_id]->next);
}

int				lm_use_way(t_node **nodes)
{
	t_pipe		*pipe;
	t_node		*prev;
	int			node_id;

	if (!lm_verif_prev(nodes, nodes[LAST]->prev_id))
		return (0);
	prev = nodes[nodes[LAST]->prev_id];
	node_id = LAST;
	while (prev)
	{
		pipe = prev->pipes;
		while (pipe && pipe->node->id != node_id)
			pipe = pipe->next;
		pipe->passed = 1;
		if (pipe->reverse)
			pipe->reverse->weight = -1;
		node_id = prev->id;
		prev = lm_find_prev(nodes, prev);
	}
	return (1);
}
