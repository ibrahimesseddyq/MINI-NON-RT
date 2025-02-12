/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_crd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:43:26 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/12 16:49:02 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

static int	cont_coor(const char *str)
{
	int	i;
	int	count;

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

bool	parse_crd(const char *str, t_vector *vector)
{
	char	**tab;

	if (cont_coor(str) != 2)
		return (false);
	tab = ft_split(str, ',');
	if (!tab || !tab[0] || !tab[1] || !tab[2])
		return (false);
	vector->x = ft_atof(tab[0]);
	vector->y = ft_atof(tab[1]);
	vector->z = ft_atof(tab[2]);
	return (true);
}
