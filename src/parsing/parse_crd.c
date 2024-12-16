/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_crd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:43:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/16 10:30:14 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

// Parse a 3D coordinate from a string

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

bool  parse_crd(const char *str,float *x ,float *y ,float *z)
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
    if (*x == (float)INT_MIN || *y == (float)INT_MIN || *z == (float)INT_MIN)
        return (false);
    return (true);
}
