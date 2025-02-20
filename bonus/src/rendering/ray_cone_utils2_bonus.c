/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:54:01 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/16 21:06:45 by sessarhi         ###   ########.fr       */
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

bool	cone_intersection(t_scene *scene,
			t_intersection *intersection, t_ray *ray)
{
	t_cone_hit	hit;
	double		t_cap;

	hit.i = scene->cone_count;
	while (hit.i--)
	{
		hit.t = hit_cone(&scene->cone[hit.i].vertex,
				&scene->cone[hit.i].axis, scene->cone[hit.i].angle, ray);
		t_cap = hit_cone_cap(&scene->cone[hit.i].vertex,
				&scene->cone[hit.i].axis, scene->cone[hit.i].angle, ray);
		hit.is_cap = (t_cap > 0 && (hit.t < 0 || t_cap < hit.t));
		if (hit.is_cap)
			hit.t = t_cap;
		if (hit.t > 0 && hit.t < intersection->distance)
			update_intersection(scene, intersection, ray, &hit);
	}
	return (intersection->hit);
}
