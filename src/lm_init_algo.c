
#include "lemin.h"

static int		lm_possible_ways(t_node **nodes)
{
	int			origin;
	int			goal;
	t_pipe		*tmp;

    origin = 0;
    goal = 0;
	tmp = nodes[FIRST]->pipes;
	while (tmp)
	{
		tmp = tmp->next;
		origin++;
	}
	tmp = nodes[LAST]->pipes;
	while (tmp)
	{
		tmp = tmp->next;
		goal++;
	}
	if (goal < origin)
		return (goal);
	return (origin);
}

static int		lm_one_step_path(t_pipe *pipe)
{
	while (pipe)
	{
		if (pipe->node->id == LAST)
			return (1);
        pipe = pipe->next;
	}
	return (0);
}

static void		lm_swap_nodes(t_farm *farm, t_node **nodes, int i, int node_id)
{
	t_node	*tmp;

	tmp = nodes[i];
    nodes[i] = nodes[node_id];
    nodes[node_id] = tmp;
    nodes[i]->id = i;
    nodes[node_id]->id = node_id;
	if (farm->end == i)
        farm->end = node_id;
}

int				lm_init_algo(t_farm *farm, t_node **nodes)
{
	if (farm->start == -1 || farm->end == -1)
		return (0);
	if (!ft_strcmp(nodes[farm->start]->pseudo, nodes[farm->end]->pseudo))
		return (1);
    lm_swap_nodes(farm, nodes, FIRST, farm->start);
    lm_swap_nodes(farm, nodes, LAST, farm->end);
	if (lm_one_step_path(nodes[0]->pipes))
		return (lm_solve_one_step(nodes[1]->pseudo, farm->nb_ants));
	if (!(farm->max_ways = lm_possible_ways(nodes)))
		return (0);
    nodes[FIRST]->ants = farm->nb_ants;
    nodes[LAST]->ants = farm->nb_ants;
	return (lm_sb_algo(farm, nodes));
}
