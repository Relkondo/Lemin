
#include "lemin.h"

static t_node			**lm_generate_nodemap(int size)
{
	t_node		**nodemap;
	int			i;

	i = 0;
	if (!(nodemap = malloc(sizeof(t_node *) * size)))
		return (NULL);
	while (i < size)
		nodemap[i++] = NULL;
	return (nodemap);
}

static unsigned int		lm_find_closest(t_node **nodes, unsigned int hash, int size)
{
	int		left;
	int		right;

	left = hash - 1;
	right = hash + 1;
	while (left >= 0 || right < size)
	{
		if (right < size && !nodes[right])
			return (right);
		if (left >= 0 && !nodes[left])
			return (left);
		right++;
		left--;
	}
	return (right);
}

unsigned int			lm_hashing(char *name, int size)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *name++))
		hash = (hash << 5) + hash + c;
	return (hash % size);
}

int						lm_nodemap(t_farm *farm, t_node *start)
{
	int			hashed;

	farm->size *= 2;
	if (!(farm->nodes = lm_generate_nodemap(farm->size)))
		return (-1);
	while (start)
	{
		hashed = lm_hashing(start->pseudo, farm->size);
		if (farm->nodes[hashed])
			hashed = lm_find_closest(farm->nodes, hashed, farm->size);
		farm->nodes[hashed] = start;
		start = start->next;
		farm->nodes[hashed]->next = NULL;
	}
	return (1);
}
