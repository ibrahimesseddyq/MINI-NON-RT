/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:01:12 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/24 20:11:21 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

FLOAT	hit_sphere(t_point *point, double radius, t_ray *ray)
{
	t_hit_sphere_info	sphere_info;

	sphere_info.oc = vector_sub(&ray->origin, point);
	sphere_info.a = vector_dot(&ray->direction, &ray->direction);
	sphere_info.b = 2.0 * vector_dot(&ray->direction, &sphere_info.oc);
	sphere_info.c = vector_dot(&sphere_info.oc, &sphere_info.oc)
		- radius * radius;
	sphere_info.discriminant = sphere_info.b * sphere_info.b - 4
		* sphere_info.a * sphere_info.c;
	if (sphere_info.discriminant < 0)
		return (-1);
	sphere_info.t1 = (-sphere_info.b - sqrt(sphere_info.discriminant))
		/ (2.0 * sphere_info.a);
	sphere_info.t2 = (-sphere_info.b + sqrt(sphere_info.discriminant))
		/ (2.0 * sphere_info.a);
	if (sphere_info.t1 > 0 && sphere_info.t2 > 0)
		sphere_info.t = fmin(sphere_info.t1, sphere_info.t2);
	else if (sphere_info.t1 > 0)
		sphere_info.t = sphere_info.t1;
	else if (sphere_info.t2 > 0)
		sphere_info.t = sphere_info.t2;
	else
		return (-1);
	return (sphere_info.t);
}

void	set_sphere_intersection_infos(t_intersection *intersection,
	int i, FLOAT t, t_scene *scene)
{
	intersection->hit = true;
	intersection->id = scene->sphere[i].id;
	intersection->distance = t;
	intersection->material = scene->sphere[i].material;
	intersection->color = scene->sphere[i].color;
}

bool	sphere_intersection(t_scene *scene,
	t_intersection *intersection, t_ray *ray)
{
	int			i;
	FLOAT		t;
	t_vector	tmp;
	t_vector	normalized;

	i = scene->sphere_count;
	while (i--)
	{
		t = hit_sphere(&scene->sphere[i].position,
				scene->sphere[i].diameter / 2.0, ray);
		if (t > 0 && t < intersection->distance)
		{
			set_sphere_intersection_infos(intersection, i, t, scene);
			tmp = vector_scale(&ray->direction, t);
			intersection->point = vector_add(&ray->origin, &tmp);
			intersection->normal
				= vector_sub(&intersection->point, &scene->sphere[i].position);
			intersection->normal = vector_normalize(&intersection->normal);
			normalized = vector_normalize(&intersection->point);
			intersection->u
				= 0.5 + (atan2(normalized.z, normalized.x) / (2 * M_PI));
			intersection->v = 0.5 - (asin(normalized.y) / M_PI);
		}
	}
	return (intersection->hit);
}
