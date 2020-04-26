#include "lemin.h"

int			lm_get_nb_ants(char *line)
{
    long		ret;

    ret = 0;
    if (*line == '+')
        line++;
    if (*line == '-')
        return (-1);
    while (*line)
    {
        if (!(*line >= '0' && *line <= '9'))
            return (-1);
        ret = ret * 10 + *(line)++ - 48;
        if (ret > 2147483647)
            return (-1);
    }
    return (ret);
}

t_farm			*lm_generate_farm(void)
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

static int		lm_exit_lemin(t_farm *farm, int error)
{
    char	*empty;
    while (get_next_line(0, &empty) > 0)
        ft_strdel(&empty);
    lm_del_farm(farm);
    if (error == 1)
    {
        write(2, "Error\n", 6);
        return (-1);
    }
    else
    {
        return (0);
    }
}

int				main(void)
{
	char		*line;
	t_farm		*farm;
	int			check;

	if (!(farm = lm_generate_farm()))
		return (-1);
	if (get_next_line(0, &line) != 1)
		return (lm_exit_lemin(farm, 1));
    farm->nb_ants = lm_get_nb_ants(line);
    ft_strdel(&line);
    if (farm->nb_ants <= 0 || !(check = lm_start_parsing(farm, line)) || check == -1)
        return lm_exit_lemin(farm, 1);
    return lm_exit_lemin(farm, 0);
}
