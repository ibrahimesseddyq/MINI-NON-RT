/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:45 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/11 22:24:43 by ibes-sed         ###   ########.fr       */
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

void	calculate_u_v(t_scene *scene,
		t_intersection *intersection, t_ray *ray, int i)
{
	t_calculate_uv	inter;

	inter.p = vector_sub(&intersection->point, &scene->cone[i].vertex);
	inter.axis = vector_normalize(&scene->cone[i].axis);
	inter.height = vector_dot(&inter.p, &inter.axis);
	inter.cone_height = vector_length(&scene->cone[i].axis);
	intersection->v = inter.height / inter.cone_height;
	inter.proj = vector_scale(&inter.axis, inter.height);
	inter.planar = vector_sub(&inter.p, &inter.proj);
	inter.up.x = 0;
	inter.up.y = 1;
	inter.up.z = 0;
	inter.right = vector_cross(&inter.axis, &inter.up);
	inter.forward = vector_cross(&inter.right, &inter.axis);
	intersection->u = 0.5 + (atan2(
				vector_dot(&inter.planar, &inter.right),
				vector_dot(&inter.planar, &inter.forward)
				) / (2 * M_PI));
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
			intersection->color = scene->cone[i].color;
			intersection->material = scene->cone[i].material;
			tmp = vector_scale(&ray->direction, t);
			intersection->point
				= vector_add(&ray->origin, &tmp);
			calculate_cone_normal(scene, intersection, &inter, i);
			calculate_u_v(scene, intersection, ray, i);
		}
	}
	return (intersection->hit);
}
