/* ************************************************************************** */
/*										                                    */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:02:06 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/26 17:29:18 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

static FLOAT	calculate_body_intersection(const t_ray *ray,
			const t_cylinder *cylinder)
{
	t_descriminant	ds;
	FLOAT			dir_dot_dir;
	FLOAT			oc_dot_dir;

	ds.oc = vector_sub(&ray->origin, &cylinder->position);
	dir_dot_dir = vector_dot(&ray->direction, &cylinder->direction);
	oc_dot_dir = vector_dot(&ds.oc, &cylinder->direction);
	ds.a = vector_dot(&ray->direction, &ray->direction) - pow(dir_dot_dir, 2);
	if (fabs(ds.a) < EPSILON)
		return (-1);
	ds.b = 2 * (vector_dot(&ray->direction, &ds.oc) - dir_dot_dir * oc_dot_dir);
	ds.c = vector_dot(&ds.oc, &ds.oc) - pow(oc_dot_dir, 2)
		- pow(cylinder->diameter / 2, 2);
	ds.discriminant = ds.b * ds.b - 4 * ds.a * ds.c;
	if (ds.discriminant < 0)
		return (-1);
	ds.t1 = (-ds.b - sqrt(ds.discriminant)) / (2.0 * ds.a);
	if (ds.t1 > EPSILON)
		return (ds.t1);
	ds.t2 = (-ds.b + sqrt(ds.discriminant)) / (2.0 * ds.a);
	if (ds.t2 > EPSILON)
		return (ds.t2);
	return (-1);
}

static bool	is_within_cylinder_height(const t_vector *point,
		const t_cylinder *cylinder)
{
	t_vector	cp;
	FLOAT		height;

	cp = vector_sub(point, &cylinder->position);
	height = vector_dot(&cp, &cylinder->direction);
	return (height >= 0 && height <= cylinder->height);
}

static bool	get_body_hit_info(t_intersection *intersection, const t_ray *ray,
							const t_cylinder *cylinder, FLOAT t)
{
	t_vector	scl_rad;
	t_vector	hit_point ;
	t_vector	cp;
	FLOAT		height;
	t_vector	proj;

	scl_rad = vector_scale(&ray->direction, t);
	hit_point = vector_add(&ray->origin, &scl_rad);
	if (!is_within_cylinder_height(&hit_point, cylinder)
		|| t >= intersection->distance)
		return (false);
	cp = vector_sub(&hit_point, &cylinder->position);
	height = vector_dot(&cp, &cylinder->direction);
	proj = vector_scale(&cylinder->direction, height);
	scl_rad = vector_sub(&cp, &proj);
	intersection->normal = vector_normalize(&scl_rad);
	intersection->point = hit_point;
	return (true);
}

static FLOAT	get_cap_intersection(t_intersection *intersection, t_caps *caps,
		const t_vector *cap_center, const t_vector *cap_normal)
{
	FLOAT		t;
	t_vector	scl_rad;
	t_vector	hit_point;
	t_vector	cp;
	t_vector	proj;

	t = hit_plane(cap_center, cap_normal, &caps->ray);
	if (t <= EPSILON || t >= caps->dmin)
		return (-1);
	scl_rad = vector_scale(&caps->ray.direction, t);
	hit_point = vector_add(&caps->ray.origin, &scl_rad);
	cp = vector_sub(&hit_point, &caps->cylinder.position);
	proj = vector_scale(&caps->cylinder.direction,
			vector_dot(&cp, &caps->cylinder.direction));
	scl_rad = vector_sub(&cp, &proj);
	if (vector_length(&scl_rad) > caps->cylinder.diameter * 0.5)
		return (-1);
	intersection->normal = *cap_normal;
	intersection->point = hit_point;
	return (t);
}

FLOAT	hit_cylinder(t_intersection *intersection, const t_ray *ray,
				const t_cylinder *cylinder, FLOAT dmin)
{
	t_cyhit		hit;
	t_caps		caps;

	caps.ray = *ray;
	caps.cylinder = *cylinder;
	caps.dmin = dmin;
	hit.body = calculate_body_intersection(ray, cylinder);
	if (hit.body > EPSILON && hit.body < caps.dmin)
		if (get_body_hit_info(intersection, ray, cylinder, hit.body))
			caps.dmin = hit.body;
	hit.bottom_normal = vector_scale(&cylinder->direction, -1);
	hit.bottom = get_cap_intersection(intersection, &caps,
			&cylinder->position, &hit.bottom_normal);
	if (hit.bottom > EPSILON && hit.bottom < caps.dmin)
		caps.dmin = hit.bottom;
	hit.top_offset = vector_scale(&cylinder->direction, cylinder->height);
	hit.top_center = vector_add(&cylinder->position, &hit.top_offset);
	hit.top = get_cap_intersection(intersection, &caps,
			&hit.top_center, &cylinder->direction);
	if (hit.top > EPSILON && hit.top < caps.dmin)
		caps.dmin = hit.top;
	if (caps.dmin < INFINITY)
		return (caps.dmin);
	return (-1);
}

