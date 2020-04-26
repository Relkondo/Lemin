#include "lemin.h"

static t_node	*lm_get_node(t_farm *farm, char *name, int size)
{
	int				left;
	int				right;
	unsigned int	hashed;

	hashed = lm_hashing(name, size);
	if (farm->nodes[hashed] && !ft_strcmp(farm->nodes[hashed]->pseudo, name))
		return (farm->nodes[hashed]);
	left = hashed - 1;
	right = hashed + 1;
	while (left >= 0 || right < size)
	{
		if (left >= 0 && farm->nodes[left] &&
			!ft_strcmp(farm->nodes[left]->pseudo, name))
			return (farm->nodes[left]);
		if (right < size && farm->nodes[right] &&
			!ft_strcmp(farm->nodes[right]->pseudo, name))
			return (farm->nodes[right]);
		left--;
		right++;
	}
	return (NULL);
}

t_pipe			*lm_init_pipe(t_node *node, t_pipe *opp)
{
	t_pipe	*new;

	if (!(new = malloc(sizeof(t_pipe))))
		return (NULL);
	new->node = node;
	new->weight = 1;
	new->passed = 0;
	new->next = NULL;
	new->reverse = opp;
	return (new);
}

static int		lm_add_pipe(t_node *node, t_pipe *pipe)
{
	t_pipe	*tmp;

	tmp = node->pipes;
	if (!tmp)
	{
		node->pipes = pipe;
		return (1);
	}
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->node->pseudo, pipe->node->pseudo))
			return (0);
		tmp = tmp->next;
	}
	if (!ft_strcmp(tmp->node->pseudo, pipe->node->pseudo))
		return (0);
	tmp->next = pipe;
	return (1);
}

static int		lm_generate_pipe(t_node *node1, t_node *node2)
{
	t_pipe	*pipe;
	t_pipe	*reverse;

	if (!(pipe = lm_init_pipe(node2, NULL)))
		return (-1);
	if (!(reverse = lm_init_pipe(node1, pipe)))
	{
		lm_del_pipes(pipe);
		return (-1);
	}
	pipe->reverse = reverse;
	if (!(lm_add_pipe(node1, pipe)) || !(lm_add_pipe(node2, reverse)))
	{
		lm_del_pipes(pipe);
		lm_del_pipes(reverse);
		return (1);
	}
	return (1);
}

int				lm_parsing_pipes(t_farm *farm, char *line)
{
	t_node	*node1;
	t_node	*node2;
	char	**nodes_id;
	int		res;
	int		i;

	i = 0;
	res = 1;
	if (!(nodes_id = lm_verif_pipe(line)))
		res = 0;
	else if (res && !ft_strcmp(nodes_id[0], nodes_id[1]))
		res = 2;
	else if (res && !(node1 = lm_get_node(farm, nodes_id[0], farm->size)))
		res = 0;
	else if (res && !(node2 = lm_get_node(farm, nodes_id[1], farm->size)))
		res = 0;
	if (res && res != 2)
		res = lm_generate_pipe(node1, node2);
	while (nodes_id && nodes_id[i])
		ft_strdel(&nodes_id[i++]);
	if (nodes_id)
		free(nodes_id);
	return (res);
}
