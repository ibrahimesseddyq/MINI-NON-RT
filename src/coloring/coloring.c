/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:26:20 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/26 10:08:52 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/color.h"

t_color color_add(t_color *a, t_color *b)
{
    t_color c;

    c.r = a->r + b->r;
    c.g = a->g + b->g;
    c.b = a->b + b->b;
    return (c);
}

t_color color_mul(t_color *a, t_color *b)
{
    t_color c;

    c.r = a->r * b->r;
    c.g = a->g * b->g;
    c.b = a->b * b->b;
    return (c);
}
 
t_color color_scale(t_color *a, FLOAT scale)
{
    t_color c;

    c.r = a->r * scale;
    c.g = a->g * scale;
    c.b = a->b * scale;
    return (c);
}

int colorToRgb(t_color *a)
{
    int r;
    int g;
    int b;
    
    r = (int)(a->r * 255.0);
    g = (int)(a->g * 255.0);
    b = (int)(a->b * 255.0);
    return (r << 16 | g << 8 | b);
}

t_color RgbToColor(int r, int g, int b)
{
    t_color c;

    c.r = (FLOAT)r / 255.0;
    c.g = (FLOAT)g / 255.0;
    c.b = (FLOAT)b / 255.0;
    return (c);
}

