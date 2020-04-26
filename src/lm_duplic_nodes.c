#include "lemin.h"

static int		lm_append(t_pipe *pipe, t_pipe *add)
{
	while (pipe->next)
		pipe = pipe->next;
	pipe->next = add;
	return (1);
}

static t_pipe	*lm_copy_pipe(t_node *node)
{
	t_pipe		*copy;
	t_pipe		*pipe;

	pipe = node->pipes;
	if (pipe->weight == -1)
	{
		node->pipes = pipe->next;
		pipe->next = NULL;
		return (pipe);
	}
	while (pipe)
	{
		if (pipe->next && pipe->next->weight == -1)
		{
			copy = pipe->next;
			pipe->next = copy->next;
			copy->next = NULL;
		}
		pipe = pipe->next;
	}
	return (copy);
}

static int		lm_copy_pipes(t_node *node, t_node *duplic)
{
	t_pipe		*pipe;
	t_pipe		*new_pipe;

	pipe = node->pipes;
	while (pipe)
	{
		if (pipe->weight == -1)
		{
			pipe = pipe->next;
			duplic->pipes = lm_copy_pipe(node);
		}
		else
		{
			if (pipe->reverse->weight != -1)
				pipe->reverse->node = duplic;
			pipe = pipe->next;
		}
	}
	if (!(new_pipe = lm_init_pipe(duplic, NULL)))
		return (-1);
	new_pipe->weight = 0;
	return (lm_append(node->pipes, new_pipe));
}

static t_node	*lm_duplic_node(t_node *node)
{
	t_node *duplic;

	if (!(duplic = malloc(sizeof(t_node))))
		return (NULL);
	if (!(duplic->pseudo = ft_strdup(node->pseudo)))
		return (NULL);
	duplic->ants = 0;
	duplic->cost = -1;
	duplic->id = -node->id;
	duplic->prev_id = -1;
	duplic->passed = 1;
	duplic->next = NULL;
	node->next = duplic;
	if (lm_copy_pipes(node, duplic) == -1)
		return (NULL);
	return (duplic);
}

int				lm_duplic_nodes(t_node ***ways)
{
	int		i;
	int		j;

	i = 0;
	while (ways[i])
	{
		j = 0;
		while (ways[i][j + 1])
		{
			if (!ways[i][j]->passed)
			{
				ways[i][j]->passed = 1;
				if (!(ways[i][j]->next = lm_duplic_node(ways[i][j])))
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}
