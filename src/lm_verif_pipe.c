#include "lemin.h"

static char	**lm_verif_node3(char **split_node)
{
	int		i;
	int		sign;

	if (!split_node)
		return (NULL);
	i = 1;
	while (i < 3)
	{
		sign = 0;
		if (split_node[i][0] == '-' || split_node[i][0] == '+')
			sign = 1;
		if (ft_strlen(split_node[i]) - sign > 10)
			return (NULL);
		i++;
	}
	return (split_node);
}

char		**lm_verif_node2(char *node_line, int i, int space)
{
	while (node_line[i])
	{
		if (!ft_isdigit(node_line[i]))
		{
			if (node_line[i] == ' ')
			{
				space++;
				if (node_line[i] == '+' || node_line[i] == '-')
					i++;
				if (space > 2 || !ft_isdigit(node_line[i + 1]))
					return (NULL);
			}
			else
				return (NULL);
		}
		i++;
	}
	if (space != 2)
		return (NULL);
	return (lm_verif_node3(ft_strsplit(node_line, ' ')));
}

char		**lm_verif_node1(char *node_line)
{
	int		i;
	int		space;

	i = 0;
	space = 0;
	while (node_line[i] && !space)
	{
		if (node_line[i] == ' ')
		{
			i++;
			space++;
			if (node_line[i] == '+' || node_line[i] == '-')
				i++;
		}
		else
			i++;
	}
	if (!ft_isdigit(node_line[i]))
		return (NULL);
	return (lm_verif_node2(node_line, i, space));
}

char		**lm_verif_pipe(char *line)
{
	int		i;
	char	check;

    check = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '-')
		{
			if (check == 1 || i == 0 || !line[i + 1])
				return (NULL);
			check++;
		}
		i++;
	}
	if (check != 1)
		return (NULL);
	return (ft_strsplit(line, '-'));
}
