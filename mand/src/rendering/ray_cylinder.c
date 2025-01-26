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

FLOAT	hit_cylinder(t_intersection *intersection, const t_ray *ray,
				const t_cylinder *cylinder, FLOAT dmin)
{
	t_cyhit		hit;

	hit.body = calculate_body_intersection(ray, cylinder);
	if (hit.body > EPSILON && hit.body < dmin)
		if (get_body_hit_info(intersection, ray, cylinder, hit.body))
			dmin = hit.body;
	hit.bottom_normal = vector_scale(&cylinder->direction, -1);
	hit.bottom = get_cap_intersection(intersection, ray, cylinder,
			&cylinder->position, &hit.bottom_normal, dmin);
	if (hit.bottom > EPSILON && hit.bottom < dmin)
		dmin = hit.bottom;
	hit.top_offset = vector_scale(&cylinder->direction, cylinder->height);
	hit.top_center = vector_add(&cylinder->position, &hit.top_offset);
	hit.top = get_cap_intersection(intersection, ray, cylinder,
			&hit.top_center, &cylinder->direction, dmin);
	if (hit.top > EPSILON && hit.top < dmin)
		dmin = hit.top;
	if (dmin < INFINITY)
		return (dmin);
	return (-1);
}

bool	cylinder_intersection(t_scene *scene,
			t_intersection *intersection, t_ray *ray)
{
	FLOAT	t;
	int		i;

	i = scene->cylinder_count;
	while (i--)
	{
		t = hit_cylinder(intersection, ray, &scene->cylinder[i],
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
