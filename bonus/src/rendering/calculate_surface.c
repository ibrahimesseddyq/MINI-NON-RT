/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_surface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:24 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/10 21:24:36 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

t_checker_config	init_checker(void)
{
	t_checker_config	config;

	config.board1 = (t_color){0, 0, 0};
	config.board2 = (t_color){255, 255, 255};
	config.size = 4;
	return (config);
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
	handle_cone_textures(scene, &params);
	if (!set)
	{
		printf("Error: no texture set id\n", intersection->id);
		// printf("intersection->color: %f %f %f\n", intersection->color.r, intersection->color.g, intersection->color.b);
		*texture_color = intersection->color;
	}
}
