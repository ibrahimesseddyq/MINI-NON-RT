/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:02:06 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/18 22:44:13 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"
//now i understand the problem very  
// Calculate intersection with cylinder's infinite body
FLOAT cydisc(const t_intersection *intersection, const t_ray *ray, const t_cylinder *cylinder)
{
    t_vector oc = vector_sub(&ray->origin, &cylinder->position);
    FLOAT a = vector_dot(&ray->direction, &ray->direction) - 
              pow(vector_dot(&ray->direction, &cylinder->direction), 2);
    if (fabs(a) < EPSILON)
        return (-1);  
    FLOAT b = 2 * (vector_dot(&ray->direction, &oc) - 
                   vector_dot(&ray->direction, &cylinder->direction) * 
                   vector_dot(&oc, &cylinder->direction));
    FLOAT c = vector_dot(&oc, &oc) - 
              pow(vector_dot(&oc, &cylinder->direction), 2) - 
              pow(cylinder->diameter / 2, 2);
    FLOAT discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    FLOAT t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    FLOAT t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    if (t1 > EPSILON)
        return (t1);
    if (t2 > EPSILON)
        return (t2);
    return (-1);
}
FLOAT hit_cylinder(t_intersection *intersection, const t_ray *ray, const t_cylinder *cylinder, FLOAT dmin)
{
    if (!intersection || !ray || !cylinder || dmin < 0)
        return (-1);
    FLOAT t_body = cydisc(intersection, ray, cylinder);
    t_vector hit_point;
    if (t_body > EPSILON && t_body < dmin)
    {
        t_vector scaled_dir = vector_scale(&ray->direction, t_body);
        hit_point = vector_add(&ray->origin, &scaled_dir);
        t_vector cp = vector_sub(&hit_point, &cylinder->position);
        FLOAT height = vector_dot(&cp, &cylinder->direction);
        if (height >= 0 && height <= cylinder->height)
        {
            t_vector proj = vector_scale(&cylinder->direction, height);
            t_vector radial = vector_sub(&cp, &proj);
            intersection->normal = vector_normalize(&radial);
            intersection->point = hit_point;
            return (t_body);
        }
    }
    t_vector bottom_normal = vector_scale(&cylinder->direction, -1);
    FLOAT t_bottom = hit_plane(&cylinder->position, &bottom_normal, ray);
    t_vector top_offset = vector_scale(&cylinder->direction, cylinder->height);
    t_point top_center = vector_add(&cylinder->position, &top_offset);
    FLOAT t_top = hit_plane(&top_center, &cylinder->direction, ray);
    FLOAT t_caps = -1;
    int is_bottom = 0;
    if (t_bottom > EPSILON && t_bottom < dmin)
    {
        t_caps = t_bottom;
        is_bottom = 1;
    }
    if (t_top > EPSILON && t_top < t_caps)
    {
        t_caps = t_top;
        is_bottom = 0;
    }
    if (t_caps > EPSILON && t_caps < dmin)
    {
        t_vector scaled_dir = vector_scale(&ray->direction, t_caps);
        hit_point = vector_add(&ray->origin, &scaled_dir);
        t_vector cp = vector_sub(&hit_point, &cylinder->position);
        t_vector proj = vector_scale(&cylinder->direction, 
                                   vector_dot(&cp, &cylinder->direction));
        t_vector radial = vector_sub(&cp, &proj);
        if (vector_length(&radial) <= cylinder->diameter / 2.0)
        {
            intersection->normal = is_bottom ? bottom_normal : cylinder->direction;
            intersection->point = hit_point;
            return (t_caps);
        }
    }
    
    return (-1);
}
//   t_vector scl = vector_scale(&ray->direction, t);
//     t_vector point = vector_add(&ray->origin, &scl);
//     t_vector cp = vector_sub(&point, &cylinder->position);
//     FLOAT height = vector_dot(&cp, &cylinder->direction);
//     if (height > 0 && height < cylinder->height && t < dmin)
//     {
//         proj = vector_scale(&cylinder->direction, height);
//         proj = vector_sub(&cp, &proj);
//         intersection->normal = vector_normalize(&proj);
//         intersection->point = point;
//         return (t);
//     }
//     t = hit_plane(&cylinder->position, &cylinder->direction, ray);
//     if (t >= 0 && t < dmin)
//     {
//         scl = vector_scale(&ray->direction, t);
//         point = vector_add(&ray->origin, &scl);
//         cp = vector_sub(&point, &cylinder->position);
//         tmp = vector_scale(&cylinder->direction,vector_dot(&cp, &cylinder->direction));
//         t_vector radial_vector = vector_sub(&cp,&tmp);
//         if (vector_length(&radial_vector) <= cylinder->diameter/2.0)
//         {
//             intersection->normal = cylinder->direction;
//             intersection->point = point;
//             return (t);
//         }
//     }
   
//     t = hit_plane(&top, &cylinder->direction, ray);
//     if (t >= 0 && t < dmin)
//     {
//         scl = vector_scale(&ray->direction, t);
//         point = vector_add(&ray->origin, &scl);
//         cp = vector_sub(&point, &top);
//         tmp =  vector_scale(&cylinder->direction, vector_dot(&cp, &cylinder->direction));
//         t_vector radial_vector = vector_sub(&cp, &tmp);
//         if (vector_length(&radial_vector) <= cylinder->diameter/2.0)
//         {
//             intersection->normal = vector_scale(&cylinder->direction, -1);
//             intersection->point = point;
//             return (t);
//         }
//     }
//     return (-1);
bool cylinder_intersection(t_scene *scene, t_intersection *intersection, t_ray *ray)
{
    int i;
    FLOAT t;
    t_vector tmp;
    
    i = scene->cylinder_count;
    while (i--)
    {
        t = hit_cylinder(intersection, ray, &scene->cylinder[i], intersection->distance);
        if (t > 0 && t < intersection->distance)
        {
            intersection->hit = true;
            intersection->id = scene->cylinder[i].id;
            intersection->distance = t;
            //(sessarhi note) the following three lines can be moved out f the loop for optimization
            intersection->color = scene->cylinder[i].color;
            // intersection->normal = vector_normalize(&intersection->normal);
        }
    }
    return (intersection->hit);
}
