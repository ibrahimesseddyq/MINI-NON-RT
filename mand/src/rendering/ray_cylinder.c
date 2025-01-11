/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:02:06 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/11 21:26:32 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

FLOAT hit_cylinder(t_intersection *intersection, t_ray *ray, t_cylinder *cylinder)
{
    t_vector oc;
    FLOAT a;
    FLOAT b;
    FLOAT c;
    FLOAT discriminant;
    FLOAT t;
    t_vector proj;
    t_vector tmp;

    cylinder->direction = vector_normalize(&cylinder->direction);
    oc = vector_sub(&ray->origin, &cylinder->position);
    a = vector_dot(&ray->direction, &ray->direction) - 
        pow(vector_dot(&ray->direction, &cylinder->direction), 2);
    if (fabs(a) < EPSILON)
        return (-1);
    b = 2 * (vector_dot(&ray->direction, &oc) - 
        vector_dot(&ray->direction, &cylinder->direction) * 
        vector_dot(&oc, &cylinder->direction));
    c = vector_dot(&oc, &oc) - 
        pow(vector_dot(&oc, &cylinder->direction), 2) - 
        pow(cylinder->diameter / 2, 2);
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t < 0)
        t = (-b + sqrt(discriminant)) / (2.0 * a);
    if (t < 0)
        return (-1);
    t_vector scl = vector_scale(&ray->direction, t);
    t_vector point = vector_add(&ray->origin, &scl);
    t_vector cp = vector_sub(&point, &cylinder->position);
    FLOAT height = vector_dot(&cp, &cylinder->direction);
    if (height >= 0 && height <= cylinder->height)
    {
        proj = vector_scale(&cylinder->direction, height);
        proj = vector_sub(&cp, &proj);
        intersection->normal = vector_normalize(&proj);
        intersection->color = cylinder->color;
        intersection->point = point;
        return (t);
    }
    t = hit_plane(&cylinder->position, &cylinder->direction, ray);
    if (t >= 0)
    {
        scl = vector_scale(&ray->direction, t);
        point = vector_add(&ray->origin, &scl);
        cp = vector_sub(&point, &cylinder->position);
        tmp = vector_scale(&cylinder->direction,vector_dot(&cp, &cylinder->direction));
        t_vector radial_vector = vector_sub(&cp,&tmp);
        if (vector_length(&radial_vector) <= cylinder->diameter/2.0)
        {
            intersection->normal = cylinder->direction;
            intersection->color = cylinder->color;
            intersection->point = point;
            return (t);
        }
    }
    tmp = vector_scale(&cylinder->direction, cylinder->height);
    t_point top = vector_add(&cylinder->position, &tmp);
    t = hit_plane(&top, &cylinder->direction, ray);
    if (t >= 0)
    {
        scl = vector_scale(&ray->direction, t);
        point = vector_add(&ray->origin, &scl);
        cp = vector_sub(&point, &top);
        tmp =  vector_scale(&cylinder->direction, vector_dot(&cp, &cylinder->direction));
        t_vector radial_vector = vector_sub(&cp, &tmp);
        if (vector_length(&radial_vector) <= cylinder->diameter/2.0)
        {
            intersection->normal = vector_scale(&cylinder->direction, -1);
            intersection->color = cylinder->color;
            intersection->point = point;
            return (t);
        }
    }
    return (-1);
}
bool cylinder_intersection(t_scene *scene, t_intersection *intersection, t_ray *ray)
{
    int i;
    FLOAT t;
    t_vector tmp;
    
    i = scene->cylinder_count;
    while (i--)
    {
        t = hit_cylinder(intersection, ray, &scene->cylinder[i]);
        if (t > 0 && t < intersection->distance)
        {
            intersection->hit = true;
            intersection->id = scene->cylinder[i].id;
            intersection->distance = t;
            //(sessarhi note) the following three lines can be moved out f the loop for optimization
            intersection->color = scene->cylinder[i].color;
            intersection->normal = vector_normalize(&intersection->normal);
        }
    }
    return (intersection->hit);
}
