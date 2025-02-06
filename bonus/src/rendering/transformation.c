/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:15 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/06 19:44:39 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	transform(int *keys, t_scene *scene)
{
	if (keys[0] == LEFT_ROW_KEY || keys[0] == UPPER_ROW_KEY
		|| keys[0] == RIGHT_ROW_KEY || keys[0] == DOWN_ROW_KEY)
		translate(keys, scene);
	else if (keys[0] == R_KEY)
		rotate(keys, scene);
	else if (keys[0] == S_KEY)
		resize(keys, scene);
}

int	transformation(int keycode, t_scene *scene)
{
	static int	keys[10];
	static int	cursor;
	int			i;

	i = 0;
	if (cursor < 10)
		keys[cursor++] = keycode;
	if (keycode == ALT_KEY)
	{
		transform(keys, scene);
		cursor = 0;
		while (i < 10)
		{
			keys[i] = 0;
			i++;
		}
	}
	if (keycode == ESC_KEY)
		return (mlx_destroy_window(scene->mlx, scene->win),
			exit(0), 1);
	return (draw(scene), 0);
}

int	search_and_translate(int *keys, int obj_id, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->sphere_count)
	{
		if (scene->sphere[i].id == obj_id)
			return (move_sphere(keys, &scene->sphere[i]), 1);
		i++;
	}
	i = 0;
	while (i < scene->cylinder_count)
	{
		if (scene->cylinder[i].id == obj_id)
			return (move_cylinder(keys, &scene->cylinder[i]), 1);
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		if (scene->plane[i].id == obj_id)
			return (move_plane(keys, &scene->plane[i]), 1);
		i++;
	}
}

void	translate(int *keys, t_scene *scene)
{
	int	obj_id;

	if ((char)keys[1] == 'c' || (char)keys[1] == 'l')
	{
		move_light_or_camera(keys, scene);
		return ;
	}
	obj_id = my_atoi(keys, 1);
	if (obj_id == -1)
		return ;
	search_and_translate(keys, obj_id, scene);
}

void	resize(int *keys, t_scene *scene)
{
	int		obj_id;
	FLOAT	ratio;

	obj_id = my_atoi(keys, 2);
	if (keys[1] == KEY_PLUS)
		ratio = 1.1;
	else if (keys[1] == KEY_MINUS)
		ratio = 0.9;
	if (obj_id == -1)
		return ;
	search_and_resize(obj_id, scene, ratio);
}
