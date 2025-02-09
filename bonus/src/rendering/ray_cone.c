/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:45 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/09 16:54:44 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

double	hit_cone(t_point *vertex, t_vector *axis, double angle, t_ray *ray)
{
	t_hit_cone_intersection	inter;
	double					t;

	inter.cos2 = cos(angle) * cos(angle);
	inter.sin2 = sin(angle) * sin(angle);
	init_cone_vars(&inter, vertex, axis, ray);
	t = get_intersection_t(&inter);
	if (t < 0 || !check_height_bounds(&inter, vertex, axis, ray))
		return (-1);
	return (t);
}

void	calculate_cone_normal(t_scene *scene,
			t_intersection *intersection, t_cone_intersection	*inter, int i)
{
	inter->cone_to_point
		= vector_sub(&intersection->point, &scene->cone[i].vertex);
	inter->axis_scaled
		= vector_scale(&scene->cone[i].axis,
			vector_dot(&inter->cone_to_point, &scene->cone[i].axis));
	inter->subs_vec
		= vector_sub(&inter->cone_to_point, &inter->axis_scaled);
	intersection->normal = vector_normalize(&inter->subs_vec);
}
t_vector cone_normal(t_cone *cone, t_vector *hit_point)
{
    t_vector to_hit;
    t_vector axis_proj;
    t_vector normal;
	t_vector scaled_vector;
    FLOAT k;

    // Vector from vertex to hit point
    to_hit = vector_sub(hit_point, &cone->vertex);

    // Compute projection on axis
    k = vector_dot(&to_hit, &cone->axis);
    axis_proj = vector_scale(&cone->axis, k);

    // Compute normal (adjusting for cone slant)
    normal = vector_sub(&to_hit, &axis_proj);
    k = tan(cone->angle * M_PI / 180.0); // Convert angle to radians
	scaled_vector = vector_scale(&cone->axis, k * vector_length(&normal));
    normal = vector_sub(&normal, &scaled_vector);

    // Normalize the result
    vector_normalize(&normal);
    return normal;
}


bool	cone_intersection(t_scene *scene,
		t_intersection *intersection, t_ray *ray)
{
	int					i;
	FLOAT				t;
	t_vector			tmp;
	t_cone_intersection	inter;

	i = scene->cone_count;
	while (i--)
	{
		t = hit_cone(&scene->cone[i].vertex, &scene->cone[i].axis,
				scene->cone[i].angle, ray);
		if (t > 0 && t < intersection->distance)
		{
			intersection->hit = true;
			intersection->id = scene->cone[i].id;
			intersection->distance = t;
			intersection->material = scene->cone[i].material;
			intersection->color = scene->cone[i].color;
			tmp = vector_scale(&ray->direction, t);
			intersection->point
				= vector_add(&ray->origin, &tmp);
			intersection->normal = cone_normal(&scene->cone[i], &intersection->point);
			vector_normalize(&intersection->normal);
		}
	}
	// printf("cone hit color[%f, %f, %f]\ndistance %f\n", intersection->color.r, intersection->color.g, intersection->color.b,intersection->distance);
	return (intersection->hit);
}
