/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:48:30 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/06 21:48:31 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	resize_sphere(int obj_id, t_scene *scene, FLOAT ratio, int i)
{
	if (scene->sphere[i].id == obj_id)
		scene->sphere[i].diameter *= ratio;
}

void	resize_cylinder(int obj_id, t_scene *scene, FLOAT ratio, int i)
{
	if (scene->cylinder[i].id == obj_id)
	{
		scene->cylinder[i].height *= ratio;
		scene->cylinder[i].diameter *= ratio;
	}
}

void	resize_plane(int obj_id, t_scene *scene, FLOAT ratio, int i)
{
	if (scene->plane[i].id == obj_id)
	{
		scene->plane[i].direction.x *= ratio;
		scene->plane[i].direction.y *= ratio;
		scene->plane[i].direction.z *= ratio;
	}
}

void	search_and_resize(int obj_id, t_scene *scene, FLOAT ratio)
{
	int	i;

	i = 0;
	while (i < scene->sphere_count)
	{
		resize_sphere(obj_id, scene, ratio, i);
		i++;
	}
	i = 0;
	while (i < scene->cylinder_count)
	{
		resize_cylinder(obj_id, scene, ratio, i);
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		resize_plane(obj_id, scene, ratio, i);
		i++;
	}
}
