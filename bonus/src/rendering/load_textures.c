/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:48:09 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/14 18:29:16 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	load_plane_texture(t_scene *scene, int i)
{
	bool	loaded_texture;
	bool	loaded_normal_texture;

	loaded_texture = load_texture(&scene->plane[i].texture, scene->mlx,
			scene->plane[i].texture_name);
	loaded_normal_texture = load_texture(&scene->plane[i].normal_texture,
			scene->mlx, scene->plane[i].normal_texture_name);
	if (!loaded_texture || !loaded_normal_texture)
	{
		clean_textures(scene);
		mlx_destroy_image(scene->mlx, scene->img.img);
		mlx_destroy_window(scene->mlx, scene->win);
		clean_exit("Error loading textures");
	}
}

void	sphere_texture(t_scene *scene, int i)
{
	bool	loaded_texture;
	bool	loaded_normal_texture;

	loaded_texture = load_texture(&scene->sphere[i].texture, scene->mlx,
			scene->sphere[i].texture_name);
	loaded_normal_texture = load_texture(&scene->sphere[i].normal_texture,
			scene->mlx, scene->sphere[i].normal_texture_name);
	if (!loaded_texture || !loaded_normal_texture)
	{
		clean_textures(scene);
		mlx_destroy_image(scene->mlx, scene->img.img);
		mlx_destroy_window(scene->mlx, scene->win);
		clean_exit("Error loading textures");
	}
}

void	cylinder_texture(t_scene *scene, int i)
{
	bool	loaded_texture;
	bool	loaded_normal_texture;

	loaded_texture = load_texture(&scene->cylinder[i].texture, scene->mlx,
			scene->cylinder[i].texture_name);
	loaded_normal_texture = load_texture(&scene->cylinder[i].normal_texture,
			scene->mlx, scene->cylinder[i].normal_texture_name);
	if (!loaded_texture || !loaded_normal_texture)
	{
		clean_textures(scene);
		mlx_destroy_image(scene->mlx, scene->img.img);
		mlx_destroy_window(scene->mlx, scene->win);
		clean_exit("Error loading textures");
	}
}

void	cone_texture(t_scene *scene, int i)
{
	bool	loaded_texture;
	bool	loaded_normal_texture;

	loaded_texture = load_texture(&scene->cone[i].texture, scene->mlx,
			scene->cone[i].texture_name);
	loaded_normal_texture = load_texture(&scene->cone[i].normal_texture,
			scene->mlx, scene->cone[i].normal_texture_name);
	if (!loaded_texture || !loaded_normal_texture)
	{
		clean_textures(scene);
		mlx_destroy_image(scene->mlx, scene->img.img);
		mlx_destroy_window(scene->mlx, scene->win);
		clean_exit("Error loading textures");
	}
}
