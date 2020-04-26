/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:11:18 by scoron            #+#    #+#             */
/*   Updated: 2018/11/14 17:01:49 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strdel(char **as)
{
	if (as == 0)
		return ;
	if (*as == 0)
		return ;
	free(*as);
	*as = 0;
}

void    ft_strlst_free(char **strlst)
{
    int		i;

    i = -1;
    while (strlst[++i] != '\0')
        free(strlst[i]);
    free(strlst);
}
