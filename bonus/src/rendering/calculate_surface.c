/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_surface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:24 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/01/28 22:23:25 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

t_color		sample_texture(t_texture *texture, FLOAT u, FLOAT v);
t_vector	calculate_bump_normal(t_texture *bump_map, FLOAT u, FLOAT v,
				t_vector *original_normal);
t_color		get_checkerboard_color(t_color color1,
				t_color color2, FLOAT u, FLOAT v, FLOAT size);
typedef struct s_texture_params
{
	t_color			*texture_color;
	t_vector		*normal;
	t_intersection	*intersection;
	int				*set;
}	t_texture_params;

typedef struct s_checker_config
{
	t_color	board1;
	t_color	board2;
	int		size;
}	t_checker_config;

static t_checker_config	init_checker(void)
{
	t_checker_config	config;

	config.board1 = (t_color){0, 0, 0};
	config.board2 = (t_color){255, 255, 255};
	config.size = 4;
	return (config);
}

static void	handle_plane_textures(t_scene *scene, t_texture_params *params)
{
	t_checker_config	checker;
	int					i;

	i = 0;
	checker = init_checker();
	while (i < scene->plane_count)
	{
		if (params->intersection->id != scene->plane[i].id)
		{
			i++;
			continue ;
		}
		if (scene->plane[i].has_checkerboard)
		{
			*(params->texture_color) = get_checkerboard_color(checker.board1,
					checker.board2, params->intersection->u,
					params->intersection->v, checker.size);
			*(params->set) = 1;
		}
		else if (scene->plane[i].texture_name)
		{
			*(params->texture_color) = sample_texture(&scene->plane[i].texture,
					params->intersection->u, params->intersection->v);
			*(params->normal) = calculate_bump_normal(&scene->plane[i].texture,
					params->intersection->u, params->intersection->v,
					&params->intersection->normal);
			*(params->set) = 1;
		}
		i++;
	}
}

static void	handle_sphere_textures(t_scene *scene, t_texture_params *params)
{
	t_checker_config	checker;
	int					i;

	i = 0;
	checker = init_checker();
	while (i < scene->sphere_count)
	{
		if (params->intersection->id != scene->sphere[i].id)
		{
			i++;
			continue ;
		}
		if (scene->sphere[i].has_checkerboard)
		{
			*(params->texture_color) = get_checkerboard_color(checker.board1,
					checker.board2, params->intersection->u,
					params->intersection->v, checker.size);
			*(params->set) = 1;
		}
		else if (scene->sphere[i].texture_name)
		{
			*(params->texture_color) = sample_texture(&scene->sphere[i].texture,
					params->intersection->u, params->intersection->v);
			*(params->normal) = calculate_bump_normal(&scene->sphere[i].texture,
					params->intersection->u, params->intersection->v,
					&params->intersection->normal);
			*(params->set) = 1;
		}
		i++;
	}
}

static void	handle_cylinder_textures(t_scene *scene, t_texture_params *params)
{
	t_checker_config	checker;
	int					i;

	i = 0;
	checker = init_checker();
	while (i < scene->cylinder_count)
	{
		if (params->intersection->id != scene->cylinder[i].id)
		{
			i++;
			continue ;
		}
		if (scene->cylinder[i].has_checkerboard)
		{
			*(params->texture_color) = get_checkerboard_color(checker.board1,
					checker.board2, params->intersection->u,
					params->intersection->v, checker.size);
			*(params->set) = 1;
		}
		else if (scene->cylinder[i].texture_name)
		{
			*(params->texture_color) = sample_texture(&scene->cylinder[i].texture,
					params->intersection->u, params->intersection->v);
			*(params->normal) = calculate_bump_normal(&scene->cylinder[i].texture,
					params->intersection->u, params->intersection->v,
					&params->intersection->normal);
			*(params->set) = 1;
		}
		i++;
	}
}

void	calculate_surface_properties(t_scene *scene,
	t_intersection *intersection,
	t_color *texture_color, t_vector *out_normal)
{
	t_texture_params	params;
	int					set;

	set = 0;
	params.texture_color = texture_color;
	params.normal = out_normal;
	params.intersection = intersection;
	params.set = &set;
	*(params.normal) = intersection->normal;
	handle_plane_textures(scene, &params);
	handle_sphere_textures(scene, &params);
	handle_cylinder_textures(scene, &params);
	if (!set)
		*texture_color = intersection->color;
}
