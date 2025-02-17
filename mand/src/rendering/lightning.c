/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:23:54 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/17 18:43:24 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

bool	check_shadow(t_scene *scene, t_ray *ray, t_intersection *intersection)
{
	t_vector		tmp;
	t_intersection	shadow_intersection;
	FLOAT			d;

	tmp = vector_sub(&scene->light.position, &intersection->point);
	d = vector_length(&tmp);
	shadow_intersection.distance = d;
	shadow_intersection.hit = false;
	shadow_intersection.id = -1;
	shadow_intersection.hit = sphere_intersection(scene,
			&shadow_intersection, ray);
	shadow_intersection.hit = cylinder_intersection(scene,
			&shadow_intersection, ray);
	shadow_intersection.hit = plane_intersection(scene,
			&shadow_intersection, ray);
	if (shadow_intersection.hit && intersection->id != shadow_intersection.id)
		return (true);
	return (false);
}

static void	ckeckeifinsd(t_color_infos *coin, t_intersection *intersection)
{
	if (!coin->is_inside)
		coin->offset_direction = 1;
	else
	{
		intersection->normal = vector_scale(&intersection->normal, -1);
		coin->offset_direction = -1;
	}
}

int	pixel_color(t_scene *scene, t_intersection *intersection, t_ray *ray)
{
	t_color_infos	coin;

	coin.is_inside = vector_dot(&intersection->normal, &ray->direction) > 0;
	ckeckeifinsd(&coin, intersection);
	coin.tmp_vector = vector_scale(&intersection->normal,
			SHADOW_BIAS * coin.offset_direction);
	coin.ray_origin = vector_add(&intersection->point, &coin.tmp_vector);
	coin.shadow_ray.origin = coin.ray_origin;
	coin.tmp_vector = vector_sub(&scene->light.position, &coin.ray_origin);
	coin.shadow_ray.direction = vector_normalize(&coin.tmp_vector);
	coin.shadow_ray.direction = vector_normalize(&coin.shadow_ray.direction);
	if (check_shadow(scene, &coin.shadow_ray, intersection))
		return (0x000000);
	coin.ambient = color_scale(&scene->ambient.color, scene->ambient.ratio);
	coin.light_dir = vector_sub(&scene->light.position, &intersection->point);
	coin.light_dir = vector_normalize(&coin.light_dir);
	coin.diff = fmax(0.0, vector_dot(&intersection->normal, &coin.light_dir));
	coin.diffuse = color_scale(&scene->light.color,
			scene->light.bratio * coin.diff);
	coin.final_color = color_add(&coin.ambient, &coin.diffuse);
	coin.final_color = color_mul(&coin.final_color, &intersection->color);
	return (colortorgb(&coin.final_color));
}
