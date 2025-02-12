/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:02 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/12 15:31:12 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

void	set_axis(int *keys, t_vector *axis)
{
	if (keys[1] == KEY_X)
	{
		axis->x = 1;
		axis->y = 0;
		axis->z = 0;
	}
	else if (keys[1] == KEY_Y)
	{
		axis->y = 1;
		axis->x = 0;
		axis->z = 0;
	}
	else if (keys[1] == KEY_Z)
	{
		axis->z = 1;
		axis->x = 0;
		axis->y = 0;
	}
}

void	rotate_camera(int *keys, t_scene *scene)
{
	t_vector	axis;
	FLOAT		angle;
	FLOAT		length;

	set_axis(keys, &axis);
	angle = M_PI / 4;
	rotate_point((t_point *)&scene->camera.direction, axis, angle);
	length = sqrt(
			scene->camera.direction.x * scene->camera.direction.x
			+ scene->camera.direction.y * scene->camera.direction.y
			+ scene->camera.direction.z * scene->camera.direction.z
			);
	if (length > 0)
	{
		scene->camera.direction.x /= length;
		scene->camera.direction.y /= length;
		scene->camera.direction.z /= length;
	}
	return ;
}

void	rotate_cylinder(int *keys, t_scene *scene, int i)
{
	t_vector	axis;
	FLOAT		angle;
	FLOAT		length;

	angle = M_PI / 4;
	set_axis(keys, &axis);
	rotate_point((t_point *)&scene->cylinder[i].direction, axis, angle);
	length = sqrt(
			scene->cylinder[i].direction.x * scene->cylinder[i].direction.x
			+ scene->cylinder[i].direction.y * scene->cylinder[i].direction.y
			+ scene->cylinder[i].direction.z * scene->cylinder[i].direction.z
			);
	if (length > 0)
	{
		scene->cylinder[i].direction.x /= length;
		scene->cylinder[i].direction.y /= length;
		scene->cylinder[i].direction.z /= length;
	}
	return ;
}

void	rotate_plane(int *keys, t_scene *scene, int i)
{
	t_vector	axis;
	FLOAT		angle;
	FLOAT		length;

	angle = M_PI / 4;
	set_axis(keys, &axis);
	rotate_point((t_point *)&scene->plane[i].direction, axis, angle);
	length = sqrt(
			scene->plane[i].direction.x * scene->plane[i].direction.x
			+ scene->plane[i].direction.y * scene->plane[i].direction.y
			+ scene->plane[i].direction.z * scene->plane[i].direction.z
			);
	if (length > 0)
	{
		scene->plane[i].direction.x /= length;
		scene->plane[i].direction.y /= length;
		scene->plane[i].direction.z /= length;
	}
	return ;
}

void	rotate(int *keys, t_scene *scene)
{
	int	obj_id;
	int	i;

	if ((char)keys[2] == 'c')
	{
		rotate_camera(keys, scene);
		return ;
	}
	obj_id = my_atoi(keys, 2);
	if (obj_id == -1)
		return ;
	i = 0;
	while (i < scene->cylinder_count)
	{
		if (scene->cylinder[i].id == obj_id)
			rotate_cylinder(keys, scene, i);
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		if (scene->plane[i].id == obj_id)
			rotate_plane(keys, scene, i);
		i++;
	}
}
