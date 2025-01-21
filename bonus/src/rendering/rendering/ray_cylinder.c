/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:02:06 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/19 19:59:45 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

static FLOAT calculate_body_intersection(const t_ray *ray, const t_cylinder *cylinder)
{
    t_vector oc = vector_sub(&ray->origin, &cylinder->position);
    FLOAT dir_dot_dir = vector_dot(&ray->direction, &cylinder->direction);
    FLOAT oc_dot_dir = vector_dot(&oc, &cylinder->direction);
    FLOAT a = vector_dot(&ray->direction, &ray->direction) - pow(dir_dot_dir, 2);
    if (fabs(a) < EPSILON)
        return (-1);   
    FLOAT b = 2 * (vector_dot(&ray->direction, &oc) - dir_dot_dir * oc_dot_dir);
    FLOAT c = vector_dot(&oc, &oc) - pow(oc_dot_dir, 2) - pow(cylinder->diameter / 2, 2);
    FLOAT discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1); 
    FLOAT sqrt_discriminant = sqrt(discriminant);
    FLOAT t1 = (-b - sqrt_discriminant) / (2.0 * a);
    if (t1 > EPSILON)
        return (t1);
    FLOAT t2 = (-b + sqrt_discriminant) / (2.0 * a);
    return (t2 > EPSILON ? t2 : -1);
}

static bool is_within_cylinder_height(const t_vector *point, const t_cylinder *cylinder)
{
    t_vector cp = vector_sub(point, &cylinder->position);
    FLOAT height = vector_dot(&cp, &cylinder->direction);
    return (height >= 0 && height <= cylinder->height);
}

static bool get_body_hit_info(t_intersection *intersection, const t_ray *ray, 
                            const t_cylinder *cylinder, FLOAT t)
{
    t_vector scaled_dir = vector_scale(&ray->direction, t);
    t_vector hit_point = vector_add(&ray->origin, &scaled_dir);
    if (!is_within_cylinder_height(&hit_point, cylinder) || t >= intersection->distance)
        return (false);
    t_vector cp = vector_sub(&hit_point, &cylinder->position);
    FLOAT height = vector_dot(&cp, &cylinder->direction);
    t_vector proj = vector_scale(&cylinder->direction, height);
    t_vector radial = vector_sub(&cp, &proj);
    intersection->normal = vector_normalize(&radial);
    intersection->point = hit_point;
    return (true);
}
static FLOAT get_cap_intersection(t_intersection *intersection, const t_ray *ray,
                                const t_cylinder *cylinder, const t_vector *cap_center,
                                const t_vector *cap_normal, FLOAT dmin)
{
    FLOAT t = hit_plane(cap_center, cap_normal, ray);
    if (t <= EPSILON || t >= dmin)
        return (-1);  
    t_vector scaled_dir = vector_scale(&ray->direction, t);
    t_vector hit_point = vector_add(&ray->origin, &scaled_dir);
    t_vector cp = vector_sub(&hit_point, &cylinder->position);
    t_vector proj = vector_scale(&cylinder->direction, 
                               vector_dot(&cp, &cylinder->direction));
    t_vector radial = vector_sub(&cp, &proj);
    if (vector_length(&radial) > cylinder->diameter / 2.0)
        return (-1); 
    intersection->normal = *cap_normal;
    intersection->point = hit_point;
    return (t);
}

FLOAT hit_cylinder(t_intersection *intersection, const t_ray *ray,
                  const t_cylinder *cylinder, FLOAT dmin)
{
    FLOAT t_body = calculate_body_intersection(ray, cylinder);
    if (t_body > EPSILON && t_body < dmin)
    {
        if (get_body_hit_info(intersection, ray, cylinder, t_body))
            dmin = t_body;
    }
    t_vector bottom_normal = vector_scale(&cylinder->direction, -1);
    FLOAT t_bottom = get_cap_intersection(intersection, ray, cylinder,
                                        &cylinder->position, &bottom_normal, dmin);
    if (t_bottom > EPSILON && t_bottom < dmin)
        dmin = t_bottom;
    t_vector top_offset = vector_scale(&cylinder->direction, cylinder->height);
    t_point top_center = vector_add(&cylinder->position, &top_offset);
    FLOAT t_top = get_cap_intersection(intersection, ray, cylinder,
                                     &top_center, &cylinder->direction, dmin);
    if (t_top > EPSILON && t_top < dmin)
        dmin = t_top;
    return (dmin < INFINITY ? dmin : -1);
}

bool cylinder_intersection(t_scene *scene, t_intersection *intersection, t_ray *ray)
{
    int i = scene->cylinder_count;
    while (i--)
    {
        FLOAT t = hit_cylinder(intersection, ray, &scene->cylinder[i],
                             intersection->distance);
        if (t > 0 && t < intersection->distance)
        {
            intersection->hit = true;
            intersection->id = scene->cylinder[i].id;
            intersection->distance = t;
            intersection->color = scene->cylinder[i].color;
        }
    }
    return (intersection->hit);
}
