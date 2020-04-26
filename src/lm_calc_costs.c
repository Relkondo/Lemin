#include "lemin.h"

static void		lm_swap_ways(t_node ***ways, int i, int j)
{
	t_node		**tmp;

	tmp = ways[i];
    ways[i] = ways[j];
    ways[j] = tmp;
}

static int		lm_splitsort(t_node ***ways, int orig, int end)
{
	int pivot;
	int i;
	int j;

	i = orig - 1;
	j = i + 1;
	pivot = ways[end][0]->cost;
	while (j < end)
	{
		if (ways[j][0]->cost <= pivot)
		{
			i++;
            lm_swap_ways(ways, i, j);
		}
		j++;
	}
    lm_swap_ways(ways, i + 1, j);
	return (i + 1);
}

static void		lm_sort_ways(t_node ***ways, int orig, int end)
{
	int pivot;

	if (orig < end)
	{
		pivot = lm_splitsort(ways, orig, end);
        lm_sort_ways(ways, orig, pivot - 1);
        lm_sort_ways(ways, pivot + 1, end);
	}
}

void			lm_recalc_costs(t_node ***ways)
{
	int		i;
	int		j;

	i = 0;
	while (ways[i])
	{
		j = 0;
		while (ways[i][j])
			j++;
        ways[i][0]->cost = j - 1;
		i++;
	}
    lm_sort_ways(ways, 0, i - 1);
}
