/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:48:46 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/08 20:56:17 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	handle_plane_maps(t_scene *scene,
	t_texture_params *params, t_checker_config	*checker, int i)
{
	// printf("plane text\n");
	if (scene->plane[i].has_color_texture)
		*(params->texture_color) = sample_texture(&scene->plane[i].texture,
				params->intersection->u, params->intersection->v, 1);
	else
		*(params->texture_color) = scene->plane[i].color;
	if (scene->plane[i].has_bump_texture)
		*(params->normal)
			= calculate_bump_normal(&scene->plane[i].normal_texture,
				params->intersection->u, params->intersection->v,
				&params->intersection->normal);
	*(params->set) = 1;
}

void	handle_plane_textures(t_scene *scene, t_texture_params *params)
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
					checker.board2, params->intersection, checker.size);
			*(params->set) = 1;
		}
		else if (scene->plane[i].texture_name)
			handle_plane_maps(scene, params, &checker, i);
		i++;
	}
}
