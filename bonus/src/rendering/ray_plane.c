/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:02:02 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/13 19:08:27 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

FLOAT	hit_plane(const t_vector *point, const t_vector *normal,
	const t_ray *ray)
{
	FLOAT		t;
	FLOAT		denom;
	t_vector	tmp;

	denom = vector_dot(normal, &ray->direction);
	if (fabs(denom) > 1e-6)
	{
		tmp = vector_sub(point, &ray->origin);
		t = vector_dot(&tmp, normal) / denom;
		if (t >= 0)
			return (t);
	}
	return (-1);
}

void	cal_uv_basis(const t_vector *normal,
			t_vector *u_axis, t_vector *v_axis)
{
	t_vector	arbitrary;

	if (fabs(normal->x) < 0.9)
		arbitrary.x = 1.0;
	else
		arbitrary.x = 0.0;
	if (fabs(normal->y) >= 0.9)
		arbitrary.y = 1.0;
	else
		arbitrary.y = 0.0;
	*u_axis = vector_cross(normal, &arbitrary);
	*u_axis = vector_normalize(u_axis);
	*v_axis = vector_cross(normal, u_axis);
	*v_axis = vector_normalize(v_axis);
}

bool	plane_intersection(const t_scene *scene,
		t_intersection *intersection, const t_ray *ray)
{
	t_plane_intersection	pint;

	pint.i = scene->plane_count;
	while (pint.i--)
	{
		pint.t = hit_plane(&scene->plane[pint.i].position,
				&scene->plane[pint.i].direction, ray);
		if (pint.t > 0 && pint.t < intersection->distance)
		{
			intersection->hit = true;
			intersection->id = scene->plane[pint.i].id;
			intersection->material = scene->plane[pint.i].material;
			intersection->distance = pint.t;
			intersection->color = scene->plane[pint.i].color;
			intersection->normal = scene->plane[pint.i].direction;
			pint.tmp = vector_scale(&ray->direction, pint.t);
			intersection->point = vector_add(&ray->origin, &pint.tmp);
			cal_uv_basis(&scene->plane[pint.i].direction, &pint.u, &pint.v);
			pint.hpr = vector_sub(&intersection->point,
					&scene->plane[pint.i].position);
			intersection->u = vector_dot(&pint.hpr, &pint.u) * 0.1;
			intersection->v = vector_dot(&pint.hpr, &pint.v) * 0.1;
		}
	}
	return (intersection->hit);
}
