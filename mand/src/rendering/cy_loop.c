/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:06:39 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/27 11:07:23 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

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
