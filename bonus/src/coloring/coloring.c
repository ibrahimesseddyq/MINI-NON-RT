/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:26:20 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/25 21:43:12 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/color.h"

t_color	color_add(t_color *a, t_color *b)
{
	t_color	c;

	c.r = fmin(a->r + b->r, 1.0);
	c.g = fmin(a->g + b->g, 1.0);
	c.b = fmin(a->b + b->b, 1.0);
	return (c);
}

t_color	color_mul(t_color *a, t_color *b)
{
	t_color	c;

	c.r = a->r * b->r;
	c.g = a->g * b->g;
	c.b = a->b * b->b;
	return (c);
}

t_color	color_scale(t_color *a, FLOAT scale)
{
	t_color	c;

	c.r = a->r * scale;
	c.g = a->g * scale;
	c.b = a->b * scale;
	return (c);
}

int	colortorgb(t_color *a)
{
	int	r;
	int	g;
	int	b;

	a->r = fmin(a->r, 1.0);
	a->g = fmin(a->g, 1.0);
	a->b = fmin(a->b, 1.0);
	r = (int)(a->r * 255.0);
	g = (int)(a->g * 255.0);
	b = (int)(a->b * 255.0);
	return (r << 16 | g << 8 | b);
}

t_color	rgbtocolor(int r, int g, int b)
{
	t_color	c;

	c.r = (FLOAT)r / 255.0;
	c.g = (FLOAT)g / 255.0;
	c.b = (FLOAT)b / 255.0;
	return (c);
}
