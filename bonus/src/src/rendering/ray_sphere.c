/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:01:12 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/22 21:58:46 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"


FLOAT hit_sphere(t_point *point, double radius, t_ray *ray)
{
    t_vector oc;
    FLOAT a;
    FLOAT b;
    FLOAT c;
    FLOAT discriminant;
    FLOAT t;
    oc = vector_sub(&ray->origin, point);
    a = vector_dot(&ray->direction, &ray->direction);
    b = 2.0 * vector_dot(&ray->direction,&oc);
    c = vector_dot(&oc, &oc) - radius * radius;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return -1;

    FLOAT t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    FLOAT t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    if (t1 > 0 && t2 > 0)
        t = fmin(t1, t2);
    else if (t1 > 0)
        t = t1;
    else if (t2 > 0)
        t = t2;
    else
        return -1;
    return t;
}

bool sphere_intersection(t_scene *scene , t_intersection *intersection , t_ray *ray)
{
    int i;
    FLOAT t;
    t_vector tmp;
    
    i = scene->sphere_count;
    while (i--)
    {
        t = hit_sphere(&scene->sphere[i].position, scene->sphere[i].diameter / 2.0, ray);
        if (t > 0 && t < intersection->distance)
        {
            intersection->hit = true;
            intersection->id = scene->sphere[i].id;
            intersection->distance = t;
            //(sessarhi note) the following three lines can be moved out f the loop for optimization
            intersection->color = scene->sphere[i].color;
            tmp = vector_scale(&ray->direction, t);
            intersection->point = vector_add(&ray->origin, &tmp);
            intersection->normal = vector_sub(&intersection->point, &scene->sphere[i].position);
            intersection->normal = vector_normalize(&intersection->normal);
            t_vector normalized = vector_normalize(&intersection->point);
            intersection->u = 0.5 + (atan2(normalized.z, normalized.x) / (2 * M_PI));
            intersection->v = 0.5 - (asin(normalized.y) / M_PI);
        }
    }
    return (intersection->hit);
}