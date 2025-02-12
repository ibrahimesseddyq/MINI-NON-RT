/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:47:59 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/11 21:13:47 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	handle_cylinder_maps(t_scene *scene,
	t_texture_params *params, int i)
{
	if (scene->cylinder[i].has_color_texture && scene->cylinder[i].texture.addr)
		*(params->texture_color) = sample_texture(&scene->cylinder[i].texture,
				params->intersection->u, params->intersection->v, 1);
	else
		*(params->texture_color) = scene->cylinder[i].color;
	if (scene->cylinder[i].has_bump_texture
		&& scene->cylinder[i].normal_texture.addr)
		*(params->normal)
			= calculate_bump_normal(&scene->cylinder[i].normal_texture,
				params->intersection->u, params->intersection->v,
				&params->intersection->normal);
	*(params->set) = 1;
}

void	handle_cylinder_textures(t_scene *scene, t_texture_params *params)
{
	t_checker_config	checker;
	int					i;

	i = 0;
	checker = init_checker();
	while (i < scene->cylinder_count)
	{
		if (params->intersection->id == scene->cylinder[i].id)
		{
			if (scene->cylinder[i].has_checkerboard)
			{
				*(params->texture_color) = get_checkerboard_color(
						checker.board1, checker.board2,
						params->intersection, checker.size);
				*(params->set) = 1;
			}
			else if (scene->cylinder[i].texture_name)
				handle_cylinder_maps(scene, params, i);
			return ;
		}
		i++;
	}
}
