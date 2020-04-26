#include "lemin.h"

static t_node	*lm_clean_mem(char **mem, t_node *room, char **line, t_node *ret)
{
	int			i;

	i = 0;
	ft_strdel(line);
	if (room)
        lm_del_node(&room);
	while (mem && mem[i])
	{
		ft_strdel(&mem[i]);
		i++;
	}
	free(mem);
	return (ret);
}

t_node			*lm_generate_nodes(t_node *end, char **line, int entry)
{
	t_node		*new;
	char		**mem;

	if (!(mem = lm_verif_node1(*line)))
		return (NULL);
	if (!(new = malloc(sizeof(t_node))))
		return (lm_clean_mem(mem, NULL, line, NULL));
	if (!(new->pseudo = ft_strdup(mem[0])))
		return (lm_clean_mem(mem, new, line, NULL));
	new->entry = entry;
	new->ants = 0;
	new->cost = (entry == 1) ? 0 : -1;
	new->id = -1;
	new->passed = 0;
	new->prev_id = -1;
	new->pipes = NULL;
	new->next = NULL;
	if ((new->x = ft_atoi(mem[1])) > INT_MAX || new->x < INT_MIN)
		return (lm_clean_mem(mem, new, line, NULL));
	if ((new->y = ft_atoi(mem[2])) > INT_MAX || new->x < INT_MIN)
		return (lm_clean_mem(mem, new, line, NULL));
	if (end)
		end->next = new;
	return (lm_clean_mem(mem, NULL, line, new));
}

t_node					**lm_index(t_farm *farm)
{
    t_node		**new;
    int			i;
    int			j;
    int			size;

    size = farm->size / 2;
    j = 0;
    i = 0;
    if (!size || !(new = malloc(sizeof(t_node *) * (size + 1))))
        return (NULL);
    new[size] = NULL;
    while (i < farm->size)
    {
        if (farm->nodes[i])
        {
            farm->nodes[i]->next = NULL;
            farm->nodes[i]->id = j;
            farm->nodes[i]->entry == -1 ? farm->end = j : 0;
            farm->nodes[i]->entry == 1 ? farm->start = j : 0;
            new[j++] = farm->nodes[i];
        }
        i++;
    }
    return (new);
}
