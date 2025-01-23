/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:02:02 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/23 20:31:59 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

FLOAT hit_plane(const t_vector *point, const t_vector *normal, const t_ray *ray)
{
    FLOAT t;
    FLOAT denom;
    t_vector tmp;

    denom = vector_dot(normal, &ray->direction);
    if (fabs(denom) > 1e-6)
    {
        tmp = vector_sub(point, &ray->origin);
        t = vector_dot(&tmp, normal) / denom;
        if (t >= 0)
            return (t);
    }
    return (-1);
}

bool plane_intersection(const t_scene *scene, t_intersection *intersection,const t_ray *ray)
{
    int i;
    FLOAT t;
    t_vector tmp;
    
    i = scene->plane_count;
    while (i--)
    {
        t = hit_plane(&scene->plane[i].position, &scene->plane[i].direction, ray);
        if (t > 0 && t < intersection->distance)
        {
            intersection->hit = true;
            intersection->id = scene->plane[i].id;
            intersection->distance = t;
            intersection->color = scene->plane[i].color;
            intersection->normal = scene->plane[i].direction;
            tmp = vector_scale(&ray->direction, t);
            intersection->point = vector_add(&ray->origin, &tmp);
        }
    }
    return (intersection->hit);
}
