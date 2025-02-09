/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:27:41 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/09 16:48:06 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

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
			intersection->material = scene->cylinder[i].material;
		}
	}
	return (intersection->hit);
}
