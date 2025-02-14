/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:19 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/14 16:42:26 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void 	clean_textures(t_scene *scene)
{
	int	i;
	i = scene->cone_count;
	while (i--)
	{
		mlx_destroy_image(scene->mlx, scene->cone[i].texture.data);
		mlx_destroy_image(scene->mlx, scene->cone[i].normal_texture.data);
	}
	i = scene->cylinder_count;
	while (i--)
	{
		mlx_destroy_image(scene->mlx, scene->cylinder[i].texture.data);
		mlx_destroy_image(scene->mlx, scene->cylinder[i].normal_texture.data);
	}
	i = scene->sphere_count;
	while (i--)
	{
		mlx_destroy_image(scene->mlx, scene->sphere[i].texture.data);
		mlx_destroy_image(scene->mlx, scene->sphere[i].normal_texture.data);
	}
	i = scene->plane_count;
	while (i--)
	{
		mlx_destroy_image(scene->mlx, scene->plane[i].texture.data);
		mlx_destroy_image(scene->mlx, scene->plane[i].normal_texture.data);
	}
}
int	hook(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	mlx_destroy_window(scene->mlx, scene->win);
	clean_textures(scene);
	clean_exit("");
	return (0);
}
