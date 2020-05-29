/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 05:37:50 by scoron            #+#    #+#             */
/*   Updated: 2020/05/28 02:50:39 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	lm_next_line(char **line)
{
	int check;

	ft_strdel(line);
	if ((check = lm_gnl(0, line)) != 1)
		return (check);
	while (*line[0] == '#')
	{
		if (!(ft_strcmp(*line, "##start")) || !(ft_strcmp(*line, "##end")))
			return (0);
		ft_strdel(line);
		check = lm_gnl(0, line);
		if (check <= 0)
			return (check);
	}
	return (check);
}

t_node		*lm_parse_nodes(char **line, t_node *end, int *res, t_node *start)
{
	static int	check = 1;

	if (*line[0] != '#')
		return (lm_generate_nodes(end, line, 0, start));
	if (!(ft_strcmp(*line, "##start")) && check > 0 && (check *= -1))
	{
		if (lm_next_line(line) != 1)
			return (NULL);
		if (!(end = lm_generate_nodes(end, line, 1, start)))
			return (NULL);
	}
	else if (!(ft_strcmp(*line, "##end")) && (check % 2) != 0 && (check *= 2))
	{
		if (lm_next_line(line) != 1)
			return (NULL);
		if (!(end = lm_generate_nodes(end, line, -1, start)))
			return (NULL);
	}
	else
		*res = 0;
	return ((*res == 0) ? NULL : end);
}

static int	lm_get_nodes(t_farm *farm, char **line)
{
	t_node	*start;
	t_node	*end;
	int		res;

	start = NULL;
	end = NULL;
	while ((res = (lm_gnl(0, line) == 1)) && (ft_strchr(*line, ' ')
				|| *line[0] == '#'))
	{
		if (*line[0] == 'L')
			return (lm_del(line, start, 0, 1));
		if (!(ft_strcmp(*line, "##start")) || !(ft_strcmp(*line, "##end"))
													|| *line[0] != '#')
		{
			if (!(end = lm_parse_nodes(line, end, &res, start)))
				return (lm_del(line, start, res, 1));
			(start == NULL) ? start = end : start;
			farm->size++;
		}
		ft_strdel(line);
	}
	res = (res == -1 ? -1 : 0);
	if (res == -1 || !farm->size)
		return (lm_del(line, start, res, 1));
	return (lm_nodemap(farm, start));
}

static int	lm_pipeline(t_farm *farm, char *line)
{
	int		res;

	res = lm_parsing_pipes(farm, line);
	ft_strdel(&line);
	if (res <= 0)
		return (-1);
	while ((res = (lm_gnl(0, &line) == 1)) && line[0] != '\0')
	{
		if (line[0] != '#' || !(ft_strcmp(line, "##start"))
							|| !(ft_strcmp(line, "##end")))
		{
			res = lm_parsing_pipes(farm, line);
			if (!res)
				break ;
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

int			lm_start_parsing(t_farm *farm)
{
	t_node		**nodes;
	char		*line;
	int			res;

	if ((res = lm_get_nodes(farm, &line)) <= 0)
		return (res);
	if (line[0] == '\0' || (!(nodes = lm_index(farm)) && line))
		ft_strdel(&line);
	if (!line || !(nodes))
		return (0);
	if ((res = lm_pipeline(farm, line)) == -1)
	{
		free(nodes);
		return (lm_del(&line, NULL, res, 0));
	}
	free(farm->nodes);
	farm->nodes = nodes;
	farm->size /= 2;
	ft_printf("\n");
	return (lm_init_algo(farm, nodes));
}
