/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:21:30 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/11 22:21:31 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	setup_plane_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->plane_count)
	{
		if (scene->plane[i].texture_name)
			load_plane_texture(scene, i);
		i++;
	}
}

void	setup_sphere_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->sphere_count)
	{
		if (scene->sphere[i].texture_name)
			sphere_texture(scene, i);
		i++;
	}
}

void	setup_cylinder_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->cylinder_count)
	{
		if (scene->cylinder[i].texture_name)
			cylinder_texture(scene, i);
		i++;
	}
}

void	setup_cone_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->cone_count)
	{
		if (scene->cone[i].texture_name)
			cone_texture(scene, i);
		i++;
	}
}
