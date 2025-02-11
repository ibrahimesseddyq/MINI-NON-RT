/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:02:02 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/11 22:22:55 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

FLOAT	hit_plane(const t_vector *point,
	const t_vector *normal, const t_ray *ray)
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

void	calculate_uv_basis(const t_vector *normal,
		t_vector *u_axis, t_vector *v_axis)
{
	t_vector	arbitrary;
	t_vector	crossed_vec1;
	t_vector	crossed_vec2;

	arbitrary.x = 1;
	arbitrary.y = 0;
	arbitrary.z = 0;
	if (fabs(vector_dot(normal, &arbitrary)) > 0.9)
		arbitrary = (t_vector){0, 1, 0};
	crossed_vec1 = vector_cross(normal, &arbitrary);
	*u_axis = vector_normalize(&crossed_vec1);
	crossed_vec2 = vector_cross(normal, u_axis);
	*v_axis = vector_normalize(&crossed_vec2);
}

bool	plane_intersection(const t_scene *scene,
		t_intersection *intersection, const t_ray *ray)
{
	int			i;
	FLOAT		t;
	t_vector	tmp;
	t_vector	relative_point;

	i = scene->plane_count;
	while (i--)
	{
		t = hit_plane(&scene->plane[i].position,
				&scene->plane[i].direction, ray);
		if (t > 0 && t < intersection->distance)
		{
			intersection->hit = true;
			intersection->id = scene->plane[i].id;
			intersection->material = scene->plane[i].material;
			intersection->distance = t;
			intersection->color = scene->plane[i].color;
			intersection->normal = scene->plane[i].direction;
			tmp = vector_scale(&ray->direction, t);
			intersection->point = vector_add(&ray->origin, &tmp);
		}
	}
	return (intersection->hit);
}
