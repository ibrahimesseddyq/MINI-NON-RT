/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_crd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:43:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/23 15:15:56 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int  cont_coor(const char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == ',')
            count++;
        i++;
    }
    return (count);
}

bool  parse_crd(const char *str,FLOAT *x ,FLOAT *y ,FLOAT *z)
{
    char **tab;
    if (cont_coor(str) != 2)
        return (false);
    tab = ft_split(str, ',');
    if (!tab || !tab[0] || !tab[1] || !tab[2])
        return (false);
    *x = ft_atof(tab[0]);
    *y = ft_atof(tab[1]);
    *z = ft_atof(tab[2]);
    free(tab);
    if (*x == (FLOAT)INT_MIN || *y == (FLOAT)INT_MIN || *z == (FLOAT)INT_MIN)
        return (false);
    return (true);
}
