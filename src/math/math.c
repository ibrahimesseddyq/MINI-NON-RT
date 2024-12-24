/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:05:04 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/24 17:35:07 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math.h"

t_vector vector_add(t_vector *a, t_vector *b)
{
    t_vector res;

    res.x = a->x + b->x;
    res.y = a->y + b->y;
    res.z = a->z + b->z;
    return (res);
}
t_vector vector_sub(t_vector *a, t_vector *b)
{
    t_vector res;

    res.x = a->x - b->x;
    res.y = a->y - b->y;
    res.z = a->z - b->z;
    return (res);
}
t_vector vector_mul(t_vector *a, t_vector *b)
{
    t_vector res;

    res.x = a->x * b->x;
    res.y = a->y * b->y;
    res.z = a->z * b->z;
    return (res);
}
t_vector vector_div(t_vector *a, t_vector *b)
{
    t_vector res;

    res.x = a->x / b->x;
    res.y = a->y / b->y;
    res.z = a->z / b->z;
    return (res);
}
t_vector vector_cross(t_vector *a, t_vector *b)
{
    t_vector res;

    res.x = a->y * b->z - a->z * b->y;
    res.y = a->z * b->x - a->x * b->z;
    res.z = a->x * b->y - a->y * b->x;
    return (res);
}

FLOAT vector_dot(t_vector *a, t_vector *b)
{
    return (a->x * b->x + a->y * b->y + a->z * b->z);
}
FLOAT vector_length(t_vector *a)
{
    return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z));
}
t_vector vector_normalize(t_vector *a)
{
    FLOAT len = vector_length(a);
    t_vector res;

    res.x = a->x / len;
    res.y = a->y / len;
    res.z = a->z / len;
    return (res);
}
t_vector vector_scale(t_vector *a, FLOAT scale)
{
    t_vector res;

    res.x = a->x * scale;
    res.y = a->y * scale;
    res.z = a->z * scale;
    return (res);
}
