/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:45 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/10 20:01:03 by sessarhi         ###   ########.fr       */
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

			t_vector p = vector_sub(&intersection->point, &scene->cone[i].vertex);
            t_vector axis = vector_normalize(&scene->cone[i].axis);
            double height = vector_dot(&p, &axis);
            double cone_height = vector_length(&scene->cone[i].axis);
            intersection->v = height / cone_height;  // Normalize height to [0,1]
            t_vector proj = vector_scale(&axis, height);
            t_vector planar = vector_sub(&p, &proj);
			t_vector up = {0, 1, 0};  // Up vector

			// Get perpendicular vectors for reference frame
			t_vector right = vector_cross(&axis, &up);
			t_vector forward = vector_cross(&right, &axis);

			// Calculate angle using atan2
			intersection->u = 0.5 + (atan2(
				vector_dot(&planar, &right),     // x component
				vector_dot(&planar, &forward)    // z component
			) / (2 * M_PI));
		}
	}
	// printf("cone hit color[%f, %f, %f]\ndistance %f\n", intersection->color.r, intersection->color.g, intersection->color.b,intersection->distance);
	return (intersection->hit);
}
