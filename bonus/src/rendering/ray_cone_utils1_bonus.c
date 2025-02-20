/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:52:05 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/16 20:56:24 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

static void	calculate_uv_cone(t_scene *scene,
			t_intersection *intersection, int i)
{
	t_uv_cone_calc	calc;

	init_uv_cone(&calc, scene, intersection, i);
	intersection->v = calc.height / calc.cone_height;
	intersection->u = 0.5 + (atan2(
				vector_dot(&calc.planar, &calc.right),
				vector_dot(&calc.planar, &calc.forward)
				) / (2 * M_PI));
}

static void	calculate_u_v(t_scene *scene,
			t_intersection *intersection, int i, bool is_cap)
{
	if (is_cap)
		calculate_uv_cap(scene, intersection, i);
	else
		calculate_uv_cone(scene, intersection, i);
}

static void	calculate_cap_normal(t_scene *scene,
			t_intersection *intersection, int i)
{
	intersection->normal = vector_normalize(&scene->cone[i].axis);
}

static void	calculate_cone_normal(t_scene *scene,
			t_intersection *intersection, t_cone_intersection *inter, int i)
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

void	update_intersection(t_scene *scene, t_intersection *intersection,
			t_ray *ray, t_cone_hit *hit)
{
	t_vector			tmp;
	t_cone_intersection	inter;

	intersection->hit = true;
	intersection->id = scene->cone[hit->i].id;
	intersection->distance = hit->t;
	intersection->color = scene->cone[hit->i].color;
	intersection->material = scene->cone[hit->i].material;
	tmp = vector_scale(&ray->direction, hit->t);
	intersection->point = vector_add(&ray->origin, &tmp);
	if (hit->is_cap)
		calculate_cap_normal(scene, intersection, hit->i);
	else
		calculate_cone_normal(scene, intersection, &inter, hit->i);
	calculate_u_v(scene, intersection, hit->i, hit->is_cap);
}
