/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:26:42 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/13 15:15:34 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	ft_copy_plane(t_tscene *tscene, t_scene *scene, int *id)
{
	int	i;

	i = 0;
	while (tscene->plane)
	{
		scene->plane->texture = (t_texture){0};
		scene->plane[i].position = tscene->plane->position;
		scene->plane[i].direction = tscene->plane->direction;
		scene->plane[i].color = tscene->plane->color;
		scene->plane[i].material = tscene->plane->material;
		scene->plane[i].texture_name = tscene->plane->texture_name;
		scene->plane[i].has_checkerboard = tscene->plane->has_checkerboard;
		scene->plane[i].normal_texture_name
			= tscene->plane->normal_texture_name;
		scene->plane[i].has_color_texture = tscene->plane->has_color_texture;
		scene->plane[i].has_bump_texture = tscene->plane->has_bump_texture;
		scene->plane[i].id = (*id)++;
		tscene->plane = tscene->plane->next;
		i++;
	}
}

void	ft_copy_sphere(t_tscene *tscene, t_scene *scene, int *id)
{
	int	i;

	i = 0;
	while (tscene->sphere)
	{
		scene->sphere->texture = (t_texture){0};
		scene->sphere[i].position = tscene->sphere->position;
		scene->sphere[i].diameter = tscene->sphere->diameter;
		scene->sphere[i].material = tscene->sphere->material;
		scene->sphere[i].has_checkerboard = tscene->sphere->has_checkerboard;
		scene->sphere[i].color = tscene->sphere->color;
		scene->sphere[i].texture_name = tscene->sphere->texture_name;
		scene->sphere[i].has_color_texture = tscene->sphere->has_color_texture;
		scene->sphere[i].has_bump_texture = tscene->sphere->has_bump_texture;
		scene->sphere[i].normal_texture_name
			= tscene->sphere->normal_texture_name;
		scene->sphere[i].id = (*id)++;
		tscene->sphere = tscene->sphere->next;
		i++;
	}
}

void	ft_copy_cylinder(t_tscene *tscene, t_scene *scene, int *id)
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
		scene->cylinder[i].has_checkerboard
			= tscene->cylinder->has_checkerboard;
		scene->cylinder[i].texture_name = tscene->cylinder->texture_name;
		scene->cylinder[i].color = tscene->cylinder->color;
		scene->cylinder[i].normal_texture_name
			= tscene->cylinder->normal_texture_name;
		scene->cylinder[i].has_color_texture
			= tscene->cylinder->has_color_texture;
		scene->cylinder[i].has_bump_texture
			= tscene->cylinder->has_bump_texture;
		scene->cylinder[i].id = (*id)++;
		tscene->cylinder = tscene->cylinder->next;
		i++;
	}
}

void	ft_copy_cone(t_tscene *tscene, t_scene *scene, int *id)
{
	int	i;

	i = 0;
	while (tscene->cone)
	{
		scene->cone->texture = (t_texture){0};
		scene->cone[i].vertex = tscene->cone->vertex;
		scene->cone[i].axis = vector_normalize(&tscene->cone->axis);
		scene->cone[i].angle = tscene->cone->angle;
		scene->cone[i].height = tscene->cone->height;
		scene->cone[i].has_checkerboard = tscene->cone->has_checkerboard;
		scene->cone[i].texture_name = tscene->cone->texture_name;
		scene->cone[i].normal_texture_name = tscene->cone->normal_texture_name;
		scene->cone[i].color = tscene->cone->color;
		scene->cone[i].has_color_texture = tscene->cone->has_color_texture;
		scene->cone[i].has_bump_texture = tscene->cone->has_bump_texture;
		scene->cone[i].material = tscene->cone->material;
		scene->cone[i].id = (*id)++;
		tscene->cone = tscene->cone->next;
		i++;
	}
}
