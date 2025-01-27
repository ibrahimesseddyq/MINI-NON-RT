/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:01:12 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/27 15:50:24 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

static inline FLOAT	hit_sphere(t_point *point, double radius, t_ray *ray)
{
	t_descriminant	dscr;

	dscr.oc = vector_sub(&ray->origin, point);
	dscr.a = vector_dot(&ray->direction, &ray->direction);
	dscr.b = 2.0 * vector_dot(&ray->direction, &dscr.oc);
	dscr.c = vector_dot(&dscr.oc, &dscr.oc) - radius * radius;
	dscr.discriminant = dscr.b * dscr.b - 4 * dscr.a * dscr.c;
	if (dscr.discriminant < 0)
		return (-1);
	dscr.t1 = (-dscr.b - sqrt(dscr.discriminant)) / (2.0 * dscr.a);
	dscr.t2 = (-dscr.b + sqrt(dscr.discriminant)) / (2.0 * dscr.a);
	if (dscr.t1 > 0 && dscr.t2 > 0)
		dscr.t = fmin(dscr.t1, dscr.t2);
	else if (dscr.t1 > 0)
		dscr.t = dscr.t1;
	else if (dscr.t2 > 0)
		dscr.t = dscr.t2;
	else
		return (-1);
	return (dscr.t);
}

bool	sphere_intersection(t_scene *scene,
		t_intersection *intersection, t_ray *ray)
{
	int			i;
	FLOAT		t;
	t_vector	tmp;

	i = scene->sphere_count;
	while (i--)
	{
		t = hit_sphere(&scene->sphere[i].position,
				scene->sphere[i].diameter / 2.0, ray);
		if (t > 0 && t < intersection->distance)
		{
			intersection->hit = true;
			intersection->id = scene->sphere[i].id;
			intersection->distance = t;
			intersection->color = scene->sphere[i].color;
			tmp = vector_scale(&ray->direction, t);
			intersection->point = vector_add(&ray->origin, &tmp);
			intersection->normal = vector_sub(&intersection->point,
					&scene->sphere[i].position);
			intersection->normal = vector_normalize(&intersection->normal);
		}
	}
	return (intersection->hit);
}
