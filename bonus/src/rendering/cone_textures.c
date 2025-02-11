/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:06:09 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/11 15:15:50 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	handle_cone_maps(t_scene *scene,
	t_texture_params *params, t_checker_config	*checker, int i)
{
	if (scene->cone[i].has_color_texture)
	{
		// printf("has color texture [%d]\n", scene->cone[i].has_color_texture);

		*(params->texture_color) = sample_texture(&scene->cone[i].texture,
				params->intersection->u, params->intersection->v, 1);
		// printf("texture_color: %f %f %f\n", params->texture_color->r, params->texture_color->g, params->texture_color->b);
	}
	else
		*(params->texture_color) = scene->cone[i].color;
	if (scene->cone[i].has_bump_texture)
		*(params->normal)
			= calculate_bump_normal(&scene->cone[i].normal_texture,
				params->intersection->u, params->intersection->v,
				&params->intersection->normal);
		*(params->set) = 1;
	// printf("is set [%d]\n", *(params->set));
// printf("texture_color: %f %f %f\n", params->texture_color->r, params->texture_color->g, params->texture_color->b);
}

void	handle_cone_textures(t_scene *scene, t_texture_params *params)
{
	t_checker_config	checker;
	int					i;

	i = 0;
	checker = init_checker();
	while (i < scene->cone_count)
	{
		if (params->intersection->id == scene->cone[i].id)
		{
			if (scene->cone[i].has_checkerboard)
			{
				*(params->texture_color) = get_checkerboard_color(
						checker.board1,checker.board2, params->intersection,
						checker.size);
				*(params->set) = 1;
			}
			else if (scene->cone[i].texture_name)
				handle_cone_maps(scene, params, &checker, i);
			return ;
		}
		i++;
	}
}
