/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_surface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:24 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/01/30 12:04:36 by ibes-sed         ###   ########.fr       */
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
			// *(params->texture_color) = sample_texture(&scene->plane[i].texture,
			// 		params->intersection->u, params->intersection->v);
			*(params->normal) = calculate_bump_normal(&scene->plane[i].normal_texture,
					params->intersection->u, params->intersection->v,
					&params->intersection->normal);
			*(params->set) = 1;
		}
		i++;
	}
}

static t_color	get_sphere_texture_color(t_sphere *sphere,
	t_intersection *intersection)
{
	t_checker_config	checker;

	if (sphere->has_checkerboard)
	{
		checker = init_checker();
		return (get_checkerboard_color(checker.board1, checker.board2,
				intersection->u, intersection->v, checker.size));
	}
	if (sphere->texture_name)
		return (sample_texture(&sphere->texture,
				intersection->u, intersection->v));
	return ((t_color){0, 0, 0, 0});
}

static t_vector	calculate_sphere_normal(t_sphere *sphere,
	t_intersection *intersection)
{
	if (sphere->texture_name)
		return (calculate_bump_normal(&sphere->normal_texture,
				intersection->u, intersection->v,
				&intersection->normal));
	return (intersection->normal);
}

static void	handle_sphere_textures(t_scene *scene, t_texture_params *params)
{
	int	i;

	i = -1;
	while (++i < scene->sphere_count)
	{
		if (params->intersection->id != scene->sphere[i].id)
		{
			i++;
			continue ;
		}
		if (scene->sphere[i].has_checkerboard || scene->sphere[i].texture_name)
		{
			*(params->texture_color) = get_sphere_texture_color(
					&scene->sphere[i], params->intersection);
			*(params->normal) = calculate_sphere_normal(
					&scene->sphere[i], params->intersection);
			*(params->set) = 1;
		}
		break ;
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
			*(params->normal) = calculate_bump_normal(&scene->cylinder[i].normal_texture,
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
