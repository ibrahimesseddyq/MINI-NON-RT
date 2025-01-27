/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 12:18:32 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/26 11:14:48 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

static int	check_pnt(const char *str)
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

bool	parse_rgb(const char *str, t_color *color)
{
	char	**tab;
	int		r;
	int		g;
	int		b;

	if (check_pnt(str) != 2)
		return (false);
	tab = ft_split(str, ',');
	if (!tab)
		return (false);
	r = rgb_value(tab[0]);
	g = rgb_value(tab[1]);
	b = rgb_value(tab[2]);
	*color = rgbtocolor(r, g, b);
	return (true);
}
