/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_scene_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:42:51 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/12 17:58:50 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

static void	copy_planes(t_tscene *tscene, t_scene *scene, int *id)
{
	int	i;

	i = 0;
	while (tscene->plane)
	{
		scene->plane[i].position = tscene->plane->position;
		scene->plane[i].direction = tscene->plane->direction;
		scene->plane[i].color = tscene->plane->color;
		scene->plane[i].id = *id;
		tscene->plane = tscene->plane->next;
		*id += 1;
		i++;
	}
}

static void	copy_spheres(t_tscene *tscene, t_scene *scene, int *id)
{
	int	i;

	i = 0;
	while (tscene->sphere)
	{
		scene->sphere[i].position = tscene->sphere->position;
		scene->sphere[i].diameter = tscene->sphere->diameter;
		scene->sphere[i].color = tscene->sphere->color;
		scene->sphere[i].id = *id;
		tscene->sphere = tscene->sphere->next;
		*id += 1;
		i++;
	}
}

static void	copy_cylinders(t_tscene *tscene, t_scene *scene, int *id)
{
	int	i;

	i = 0;
	while (tscene->cylinder)
	{
		scene->cylinder[i].position = tscene->cylinder->position;
		scene->cylinder[i].direction = vector_normalize(
				&tscene->cylinder->direction);
		scene->cylinder[i].diameter = tscene->cylinder->diameter;
		scene->cylinder[i].height = tscene->cylinder->height;
		scene->cylinder[i].color = tscene->cylinder->color;
		scene->cylinder[i].id = *id;
		tscene->cylinder = tscene->cylinder->next;
		*id += 1;
		i++;
	}
}

void	copy_tscene(t_tscene *tscene, t_scene *scene)
{
	int	id;

	id = 0;
	if (tscene->is_a_set == false || tscene->is_c_set == false
		|| tscene->is_l_set == false)
		clean_exit("Error: Missing scene data");
	scene->ambient = tscene->ambient;
	scene->camera = tscene->camera;
	scene->light = tscene->light;
	scene->cylinder = arena_alloc(*get_arena(),
			sizeof(t_cylinder) * tscene->cylinder_size);
	scene->plane = arena_alloc(*get_arena(),
			sizeof(t_plane) * tscene->plane_size);
	scene->sphere = arena_alloc(*get_arena(),
			sizeof(t_sphere) * tscene->sphere_size);
	scene->cylinder_count = tscene->cylinder_size;
	scene->plane_count = tscene->plane_size;
	scene->sphere_count = tscene->sphere_size;
	scene->viewport_dist = 1.0;
	copy_planes(tscene, scene, &id);
	copy_spheres(tscene, scene, &id);
	copy_cylinders(tscene, scene, &id);
}
