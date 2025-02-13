/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:48:09 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/12 20:42:54 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	load_plane_texture(t_scene *scene, int i)
{
	load_texture(&scene->plane[i].texture, scene->mlx,
		scene->plane[i].texture_name);
	load_texture(&scene->plane[i].normal_texture,
		scene->mlx, scene->plane[i].normal_texture_name);
}

void	sphere_texture(t_scene *scene, int i)
{
	load_texture(&scene->sphere[i].texture, scene->mlx,
		scene->sphere[i].texture_name);
	load_texture(&scene->sphere[i].normal_texture,
		scene->mlx, scene->sphere[i].normal_texture_name);
}

void	cylinder_texture(t_scene *scene, int i)
{
	load_texture(&scene->cylinder[i].texture, scene->mlx,
		scene->cylinder[i].texture_name);
	load_texture(&scene->cylinder[i].normal_texture,
		scene->mlx, scene->cylinder[i].normal_texture_name);
}

void	cone_texture(t_scene *scene, int i)
{
	load_texture(&scene->cone[i].texture, scene->mlx,
		scene->cone[i].texture_name);
	load_texture(&scene->cone[i].normal_texture,
		scene->mlx, scene->cone[i].normal_texture_name);
}
