/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:02:02 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/13 02:50:46 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

FLOAT	hit_plane(const t_vector *point,
	const t_vector *normal, const t_ray *ray)
{
	FLOAT		t;
	FLOAT		denom;
	t_vector	tmp;

	bzero(&tmp, sizeof(t_vector));
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

void	plane_uv(const t_plane *plane, const t_intersection *intersection, FLOAT *u, FLOAT *v)
{
	t_vector	local_point;
	t_vector	u_axis;
	t_vector	v_axis;
	FLOAT		u_scale;
	FLOAT		v_scale;

	if (plane->texture.width == 0 || plane->texture.height == 0)
	{
		*u = 0;
		*v = 0;
		return ;
	}
	u_scale = 4.0;
	v_scale = 4.0;
	u_axis = vector_cross(&plane->direction, &(t_vector){0, 1, 0});
	if (vector_length(&u_axis) == 0)
		u_axis = vector_cross(&plane->direction, &(t_vector){1, 0, 0});
	v_axis = vector_cross(&plane->direction, &u_axis);
	local_point = vector_sub(&intersection->point, &plane->position);
	*u = vector_dot(&local_point, &u_axis) / u_scale;
	*v = vector_dot(&local_point, &v_axis) / v_scale;
}

bool	plane_intersection(const t_scene *scene,
		t_intersection *intersection, const t_ray *ray)
{
	int			i;
	FLOAT		t;
	t_vector	tmp;

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
			if (scene->plane[i].has_checkerboard)
				plane_uv(&scene->plane[i], intersection, &intersection->u, &intersection->v);
		}
	}
	return (intersection->hit);
}
