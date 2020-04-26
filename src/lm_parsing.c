#include "lemin.h"

static int		lm_del(char **line, t_node *current_node, int res)
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
	ft_strdel(line);
	return (res);
}

static t_node	*lm_parse_nodes(char **line, t_node *end, int *res)
{
    static int	check = 1;

    if ((*line)[0] != '#')
        return (lm_generate_nodes(end, line, 0));
    if (!(ft_strcmp(*line, "##start") && check > 0 && (check *= -1)))
    {
        ft_strdel(line);
        if (get_next_line(0, line) != 1)
            return (NULL);
        if (!(end = lm_generate_nodes(end, line, 1)))
            return (NULL);
    }
    else if (!(ft_strcmp(*line, "##end")) && (check % 2) != 0 && (check *= 2))
    {
        ft_strdel(line);
        if (get_next_line(0, line) != 1)
            return (NULL);
        if (!(end = lm_generate_nodes(end, line, -1)))
            return (NULL);
    }
    else
        *res = 0;
    return ((*res == 0) ? NULL : end);
}

static int		lm_get_nodes(t_farm *farm, char **line)
{
	t_node	*start;
	t_node *end;
	int		res;

    start = NULL;
    end = NULL;
	while ((res = (get_next_line(0, line) == 1)) && (ft_strchr(*line, ' ')
                                                     || *line[0] == '#'))
	{
		if (*line[0] == 'L')
			return (lm_del(line, start, 0));
		if (((*line)[0] == '#' && (*line)[1] == '#') || *line[0] != '#')
		{
			if (!(end = lm_parse_nodes(line, end, &res)))
				return (lm_del(line, start, res));
            (start == NULL) ? start = end : start;
			farm->size++;
		}
		ft_strdel(line);
	}
	if (res == -1)
		return (lm_del(line, start, -1));
	if (!farm->size)
		return (lm_del(line, start, 0));
	return (lm_nodemap(farm, start));
}

static int		lm_pipeline(t_farm *farm, char *line)
{
	int		res;

	if ((res = lm_parsing_pipes(farm, line)) == -1 || !res)
		return (-1);
	ft_strdel(&line);
	while ((res = (get_next_line(0, &line) == 1)) && line[0] != '\0')
	{
		if (line[0] != '#')
		{
            res = lm_parsing_pipes(farm, line);
			if (!res)
			{
                lm_del(&line, NULL, 0);
				break ;
			}
			if (res == -1)
				return (-1);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (res == -1)
		return (-1);
	return (1);
}

int				lm_start_parsing(t_farm *farm, char *line)
{
	t_node		**nodes;
	int			res;

	if ((res = lm_get_nodes(farm, &line)) == -1 || !res)
		return (res);
	if (!line || line[0] == '\0' || !(nodes = lm_index(farm)))
		return (0);
	if ((res = lm_pipeline(farm, line)) == -1)
	{
		free(nodes);
		return (lm_del(&line, NULL, res));
	}
	free(farm->nodes);
    farm->nodes = nodes;
    farm->size /= 2;
	ft_printf("\n");
	return (lm_init_algo(farm, nodes));
}
