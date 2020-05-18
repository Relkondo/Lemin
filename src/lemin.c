/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 05:36:36 by scoron            #+#    #+#             */
/*   Updated: 2020/05/18 05:46:11 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	lm_exit_lemin(t_farm *farm, char **line, int error)
{
	char	*empty;
	int		i;

	ft_strdel(line);
	i = 0;
	while (get_next_line_lm(0, &empty) > 0 && i++ < 10000)
		ft_strdel(&empty);
	ft_strdel(&empty);
	lm_del_farm(farm);
	if (error == 1)
	{
		write(2, "ERROR\n", 6);
		return (-1);
	}
	else
	{
		return (0);
	}
}

int			lm_get_nb_ants(char **line)
{
	long		numb;
	char		*li;

	while (*line[0] == '#' && ft_strcmp(*line, "##start") &&
			ft_strcmp(*line, "##end"))
	{
		ft_strdel(line);
		if (get_next_line_lm(0, line) != 1)
			return (-1);
	}
	li = *line;
	numb = 0;
	if (*li == '+')
		li++;
	if (*li == '-')
		return (-1);
	while (*li)
	{
		if (!(*li >= '0' && *li <= '9'))
			return (-1);
		numb = numb * 10 + *(li)++ - 48;
		if (numb > 2147483647)
			return (-1);
	}
	return (numb);
}

t_farm		*lm_generate_farm(void)
{
	t_farm		*farm;

	if (!(farm = malloc(sizeof(t_farm))))
		return (NULL);
	farm->size = 0;
	farm->nodes = NULL;
	farm->start = -1;
	farm->end = -1;
	farm->steps = -1;
	farm->max_ways = 0;
	return (farm);
}

int			main(void)
{
	char		*line;
	t_farm		*farm;
	int			check;

	if (!(farm = lm_generate_farm()))
		return (-1);
	if (get_next_line_lm(0, &line) != 1)
		return (lm_exit_lemin(farm, &line, 1));
	if ((farm->nb_ants = lm_get_nb_ants(&line)) <= 0)
		return (lm_exit_lemin(farm, &line, 1));
	if ((check = lm_start_parsing(farm)) <= 0)
		return (lm_exit_lemin(farm, &line, 1));
	return (lm_exit_lemin(farm, &line, 0));
}
