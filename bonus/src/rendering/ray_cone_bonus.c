/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:45 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/16 21:06:39 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

static void	init_cap_calc(t_cap_calc *calc, t_vector *axis,
			double angle, t_point *vertex)
{
	calc->axis_normalized = vector_normalize(axis);
	calc->height = vector_length(axis);
	calc->base_radius = calc->height * tan(angle);
	calc->scaled_axis = vector_scale(&calc->axis_normalized, calc->height);
	calc->base_center = vector_add(vertex, &calc->scaled_axis);
}

double	hit_cone_cap(t_point *vertex, t_vector *axis, double angle, t_ray *ray)
{
	t_cap_calc	calc;

	init_cap_calc(&calc, axis, angle, vertex);
	calc.denom = vector_dot(&ray->direction, &calc.axis_normalized);
	if (fabs(calc.denom) < EPSILON)
		return (-1);
	calc.to_center = vector_sub(&calc.base_center, &ray->origin);
	calc.t = vector_dot(&calc.to_center, &calc.axis_normalized) / calc.denom;
	calc.hi = vector_scale(&ray->direction, calc.t);
	calc.hit_point = vector_add(&ray->origin, &calc.hi);
	calc.v = vector_sub(&calc.hit_point, &calc.base_center);
	if (vector_dot(&calc.v, &calc.v) <= calc.base_radius * calc.base_radius)
		return (calc.t);
	return (-1);
}

static void	init_uv_cap(t_uv_cap_calc *calc, t_scene *scene,
			t_intersection *intersection, int i)
{
	calc->axis = vector_normalize(&scene->cone[i].axis);
	calc->height = vector_length(&scene->cone[i].axis);
	calc->scaled_axis = vector_scale(&calc->axis, calc->height);
	calc->base_center = vector_add(&scene->cone[i].vertex, &calc->scaled_axis);
	calc->to_hit = vector_sub(&intersection->point, &calc->base_center);
	calc->up = (t_vector){0, 1, 0};
	calc->right = vector_cross(&calc->axis, &calc->up);
	calc->forward = vector_cross(&calc->right, &calc->axis);
}

void	calculate_uv_cap(t_scene *scene,
			t_intersection *intersection, int i)
{
	t_uv_cap_calc	calc;

	init_uv_cap(&calc, scene, intersection, i);
	calc.right = vector_normalize(&calc.right);
	calc.forward = vector_normalize(&calc.forward);
	calc.base_radius = calc.height * tan(scene->cone[i].angle);
	calc.dx = vector_dot(&calc.to_hit, &calc.right);
	calc.dy = vector_dot(&calc.to_hit, &calc.forward);
	calc.distance = sqrt(calc.dx * calc.dx + calc.dy * calc.dy);
	intersection->u = 0.5 + (atan2(calc.dy, calc.dx) / (2 * M_PI));
	intersection->v = calc.distance / calc.base_radius;
}

void	init_uv_cone(t_uv_cone_calc *calc, t_scene *scene,
			t_intersection *intersection, int i)
{
	calc->p = vector_sub(&intersection->point, &scene->cone[i].vertex);
	calc->axis = vector_normalize(&scene->cone[i].axis);
	calc->height = vector_dot(&calc->p, &calc->axis);
	calc->cone_height = vector_length(&scene->cone[i].axis);
	calc->proj = vector_scale(&calc->axis, calc->height);
	calc->planar = vector_sub(&calc->p, &calc->proj);
	calc->up = (t_vector){0, 1, 0};
	calc->right = vector_cross(&calc->axis, &calc->up);
	calc->forward = vector_cross(&calc->right, &calc->axis);
}
