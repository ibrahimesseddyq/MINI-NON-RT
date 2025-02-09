/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:02:06 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/09 16:12:08 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

static bool	get_body_hit_info(t_intersection *intersection, const t_ray *ray,
							const t_cylinder *cylinder, FLOAT t)
{
	t_body_hit_info	hit_infos;

	hit_infos.scaled_dir = vector_scale(&ray->direction, t);
	hit_infos.hit_point = vector_add(&ray->origin, &hit_infos.scaled_dir);
	if (!is_within_cylinder_height(&hit_infos.hit_point, cylinder)
		|| t >= intersection->distance)
		return (false);
	hit_infos.cp = vector_sub(&hit_infos.hit_point, &cylinder->position);
	hit_infos.height = vector_dot(&hit_infos.cp, &cylinder->direction);
	hit_infos.proj = vector_scale(&cylinder->direction, hit_infos.height);
	hit_infos.radial = vector_sub(&hit_infos.cp, &hit_infos.proj);
	intersection->normal = vector_normalize(&hit_infos.radial);
	intersection->point = hit_infos.hit_point;
	return (true);
}

static FLOAT	get_cap_intersection(t_cap_intersection_params params)
{
	t_cap_intersection	cap_infos;

	cap_infos.t = hit_plane(params.cap_center, params.cap_normal, params.ray);
	if (cap_infos.t <= EPSILON || cap_infos.t >= params.dmin)
		return (-1);
	cap_infos.scaled_dir = vector_scale(&params.ray->direction, cap_infos.t);
	cap_infos.hit_point
		= vector_add(&params.ray->origin, &cap_infos.scaled_dir);
	cap_infos.cp = vector_sub(&cap_infos.hit_point, &params.cylinder->position);

	cap_infos.proj = vector_scale(&params.cylinder->direction,
			vector_dot(&cap_infos.cp, &params.cylinder->direction));
	cap_infos.radial = vector_sub(&cap_infos.cp, &cap_infos.proj);
	if (vector_length(&cap_infos.radial) > params.cylinder->diameter / 2.0)
		return (-1);
	params.intersection->normal = *params.cap_normal;
	params.intersection->point = cap_infos.hit_point;
	return (cap_infos.t);
}

t_cap_intersection_params	build_cap_intersection_param(
					t_intersection *intersection,
					const t_ray *ray,
					const t_cylinder *cylinder, FLOAT dmin)
{
	t_cap_intersection_params	params;

	params.intersection = intersection;
	params.ray = (t_ray *)ray;
	params.cylinder = (t_cylinder *)cylinder;
	params.dmin = dmin;
	params.cap_center = (t_vector *)&cylinder->position;
	params.cap_normal = (t_vector *)&cylinder->direction;
	return (params);
}

FLOAT	hit_cylinder(t_intersection *intersection, const t_ray *ray,
					const t_cylinder *cylinder, FLOAT dmin)
{
	t_hit_cy					hit_infos;
	t_cap_intersection_params	params;

	hit_infos.t_body = calculate_body_intersection(ray, cylinder);
	if (hit_infos.t_body > EPSILON && hit_infos.t_body < dmin)
	{
		if (get_body_hit_info(intersection, ray, cylinder, hit_infos.t_body))
			dmin = hit_infos.t_body;
	}
	params = build_cap_intersection_param(intersection, ray, cylinder, dmin);
	hit_infos.bottom_normal = vector_scale(&cylinder->direction, -1);
	hit_infos.t_bottom = get_cap_intersection(params);
	if (hit_infos.t_bottom > EPSILON && hit_infos.t_bottom < dmin)
		dmin = hit_infos.t_bottom;
	hit_infos.top_offset = vector_scale(&cylinder->direction, cylinder->height);
	hit_infos.top_center
		= vector_add(&cylinder->position, &hit_infos.top_offset);
	params.cap_normal = &hit_infos.bottom_normal;
	params.cap_center = &hit_infos.top_center;
	hit_infos.t_top = get_cap_intersection(params);
	if (hit_infos.t_top > EPSILON && hit_infos.t_top < dmin)
		dmin = hit_infos.t_top;
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
			intersection->material = scene->cylinder[i].material;
			intersection->hit = true;
			intersection->id = scene->cylinder[i].id;
			intersection->distance = t;
			intersection->color = scene->cylinder[i].color;
		}
	}
	return (intersection->hit);
}
