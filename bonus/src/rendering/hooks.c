/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:35:37 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/14 18:21:15 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

static void	clean_textures_sp_pl(t_scene *scene)
{
	int	i;

	i = scene->sphere_count;
	while (i--)
	{
		if (scene->sphere[i].texture.data)
			mlx_destroy_image(scene->mlx, scene->sphere[i].texture.data);
		if (scene->sphere[i].normal_texture.data)
			mlx_destroy_image(scene->mlx, scene->sphere[i].normal_texture.data);
	}
	i = scene->plane_count;
	while (i--)
	{
		if (scene->plane[i].texture.data)
			mlx_destroy_image(scene->mlx, scene->plane[i].texture.data);
		if (scene->plane[i].normal_texture.data)
			mlx_destroy_image(scene->mlx, scene->plane[i].normal_texture.data);
	}
}

void	clean_textures(t_scene *scene)
{
	int	i;

	i = scene->cone_count;
	while (i--)
	{
		if (scene->cone[i].texture.data)
			mlx_destroy_image(scene->mlx, scene->cone[i].texture.data);
		if (scene->cone[i].normal_texture.data)
			mlx_destroy_image(scene->mlx, scene->cone[i].normal_texture.data);
	}
	i = scene->cylinder_count;
	while (i--)
	{
		if (scene->cylinder[i].texture.data)
			mlx_destroy_image(scene->mlx, scene->cylinder[i].texture.data);
		if (scene->cylinder[i].normal_texture.data)
			mlx_destroy_image(scene->mlx,
				scene->cylinder[i].normal_texture.data);
	}
	clean_textures_sp_pl(scene);
}

int	hook(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	mlx_destroy_window(scene->mlx, scene->win);
	clean_textures(scene);
	clean_exit("");
	return (0);
}
