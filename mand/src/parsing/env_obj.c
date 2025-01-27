/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:09:02 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/27 15:52:14 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

int	process_a(char **inf, t_tscene *tscene)
{
	if (!inf[1] || !inf[2] || inf[3])
		return (1);
	if (tscene->is_a_set == true)
		return (printf("Error multiple Ambient lights\n"), 1);
	tscene->ambient.ratio = ft_atof(inf[1]);
	if (!parse_rgb(inf[2], &tscene->ambient.color)
		|| tscene->ambient.ratio < 0 || tscene->ambient.ratio > 1)
		return (1);
	tscene->is_a_set = true;
	return (0);
}

int	process_c(char **inf, t_tscene *t_scene)
{
	t_vector	normalized_dir;

	if (!inf[1] || !inf[2] || !inf[3] || inf[4])
		return (1);
	if (t_scene->is_c_set == true)
		return (printf("Error multiple Cameras\n"), 1);
	t_scene->camera.fov = ft_atoi(inf[3]);
	if (!parse_crd(inf[1], &t_scene->camera.position)
		|| !parse_crd(inf[2], &t_scene->camera.direction))
		return (1);
	normalized_dir = vector_normalize(&t_scene->camera.direction);
	t_scene->camera.direction.x = normalized_dir.x;
	t_scene->camera.direction.y = normalized_dir.y;
	t_scene->camera.direction.z = normalized_dir.z;
	if (t_scene->camera.fov > 180 || t_scene->camera.fov < 0
		|| t_scene->camera.direction.x < -1 || t_scene->camera.direction.x
		> 1 || t_scene->camera.direction.y < -1
		|| t_scene->camera.direction.y > 1
		|| t_scene->camera.direction.z < -1 || t_scene->camera.direction.z > 1)
		return (1);
	t_scene->is_c_set = true;
	return (0);
}

int	process_l(char **inf, t_tscene *t_scene)
{
	if (!inf[1] || !inf[2] || !inf[3] || inf[4])
		return (1);
	if (t_scene->is_l_set == true)
		return (printf("Error multiple Lights\n"), 1);
	t_scene->light.bratio = ft_atof(inf[2]);
	if (!parse_crd(inf[1], &t_scene->light.position)
		|| !parse_rgb(inf[3], &t_scene->light.color)
		|| t_scene->light.bratio < 0 || t_scene->light.bratio > 1)
		return (1);
	t_scene->is_l_set = true;
	return (0);
}
