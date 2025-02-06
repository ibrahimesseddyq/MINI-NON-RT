/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_scene_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:42:51 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/06 21:34:26 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

static void	ft_copy_plane(t_tscene *tscene, t_scene *scene, int *id)
{
	int	i;

	i = 0;
	while (tscene->plane)
	{
		scene->plane[i].position = tscene->plane->position;
		scene->plane[i].direction = tscene->plane->direction;
		scene->plane[i].color = tscene->plane->color;
		scene->plane[i].material = tscene->plane->material;
		scene->plane[i].texture_name = tscene->plane->texture_name;
		scene->plane[i].normal_texture_name = tscene->plane->normal_texture_name;
		scene->plane[i].has_color_texture = tscene->plane->has_color_texture;
		scene->plane[i].has_bump_texture = tscene->plane->has_bump_texture;

		scene->plane[i].id = (*id)++;
		tscene->plane = tscene->plane->next;
		i++;
	}
}

static void	ft_copy_sphere(t_tscene *tscene, t_scene *scene, int *id)
{
	int	i;

	i = 0;
	while (tscene->sphere)
	{
		scene->sphere[i].position = tscene->sphere->position;
		scene->sphere[i].diameter = tscene->sphere->diameter;
		scene->sphere[i].material = tscene->sphere->material;
		scene->sphere[i].color = tscene->sphere->color;
		scene->sphere[i].texture_name = tscene->sphere->texture_name;
		scene->sphere[i].has_color_texture = tscene->sphere->has_color_texture;
		scene->sphere[i].has_bump_texture = tscene->sphere->has_bump_texture;
		scene->sphere[i].normal_texture_name = tscene->sphere->normal_texture_name;
		scene->sphere[i].id = (*id)++;
		tscene->sphere = tscene->sphere->next;
		i++;
	}
}

static void	ft_copy_cylinder(t_tscene *tscene, t_scene *scene, int *id)
{
	int	i;

	i = 0;
	while (tscene->cylinder)
	{
		scene->cylinder[i].position = tscene->cylinder->position;
		scene->cylinder[i].direction
			= vector_normalize(&tscene->cylinder->direction);
		scene->cylinder[i].diameter = tscene->cylinder->diameter;
		scene->cylinder[i].height = tscene->cylinder->height;
		scene->cylinder[i].material = tscene->cylinder->material;
		scene->cylinder[i].texture_name = tscene->cylinder->texture_name;
		scene->cylinder[i].color = tscene->cylinder->color;
		scene->cylinder[i].normal_texture_name = tscene->cylinder->normal_texture_name;
		scene->cylinder[i].has_color_texture = tscene->cylinder->has_color_texture;
		scene->cylinder[i].has_bump_texture = tscene->cylinder->has_bump_texture;
		scene->cylinder[i].id = (*id)++;
		tscene->cylinder = tscene->cylinder->next;
		i++;
	}
}

static void	ft_copy_light(t_tscene *tscene, t_scene *scene, int *id)
{
	int	i;

	i = 0;
	while (tscene->light)
	{
		scene->light[i].position = tscene->light->position;
		scene->light[i].bratio = tscene->light->bratio;
		scene->light[i].color = tscene->light->color;
		scene->light[i].id = (*id)++;
		tscene->light = tscene->light->next;
		i++;
	}
}

void	copy_tscene(t_tscene *tscene, t_scene *scene)
{
	int	id;

	scene->ambient = tscene->ambient;
	scene->camera = tscene->camera;
	scene->cylinder = arena_alloc(*get_arena(),
			sizeof(t_cylinder) * tscene->cylinder_size);
	scene->plane = arena_alloc(*get_arena(),
			sizeof(t_plane) * tscene->plane_size);
	scene->sphere = arena_alloc(*get_arena(),
			sizeof(t_sphere) * tscene->sphere_size);
	scene->light = arena_alloc(*get_arena(),
			sizeof(t_light) * tscene->light_size);
	scene->cylinder_count = tscene->cylinder_size;
	scene->plane_count = tscene->plane_size;
	scene->sphere_count = tscene->sphere_size;
	scene->light_count = tscene->light_size;
	scene->viewport_dist = 1.0;
	id = 0;
	ft_copy_plane(tscene, scene, &id);
	ft_copy_sphere(tscene, scene, &id);
	ft_copy_cylinder(tscene, scene, &id);
	ft_copy_light(tscene, scene, &id);
}
