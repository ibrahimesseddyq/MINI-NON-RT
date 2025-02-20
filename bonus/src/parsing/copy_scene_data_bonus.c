/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_scene_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:42:51 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/13 14:48:10 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

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

void	copy_objects(t_tscene *tscene, t_scene *scene, int *id)
{
	ft_copy_plane(tscene, scene, id);
	ft_copy_sphere(tscene, scene, id);
	ft_copy_cylinder(tscene, scene, id);
	ft_copy_cone(tscene, scene, id);
	ft_copy_light(tscene, scene, id);
}

void	copy_tscene(t_tscene *tscene, t_scene *scene)
{
	int	id;

	scene->ambient = tscene->ambient;
	scene->camera = tscene->camera;
	scene->cylinder = arena_alloc(*get_arena(), sizeof(t_cylinder)
			* tscene->cylinder_size);
	scene->plane = arena_alloc(*get_arena(),
			sizeof(t_plane) * tscene->plane_size);
	scene->sphere = arena_alloc(*get_arena(),
			sizeof(t_sphere) * tscene->sphere_size);
	scene->cone = arena_alloc(*get_arena(), sizeof(t_cone) * tscene->cone_size);
	scene->light = arena_alloc(*get_arena(),
			sizeof(t_light) * tscene->light_size);
	scene->cylinder_count = tscene->cylinder_size;
	scene->plane_count = tscene->plane_size;
	scene->sphere_count = tscene->sphere_size;
	scene->cone_count = tscene->cone_size;
	scene->light_count = tscene->light_size;
	scene->viewport_dist = 1.0;
	id = 0;
	copy_objects(tscene, scene, &id);
}
