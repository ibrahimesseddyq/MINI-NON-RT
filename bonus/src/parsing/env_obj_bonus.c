/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_obj_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:09:02 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/20 11:00:19 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

int	is_norm(t_vector *v)
{
	FLOAT	len;

	if (v->x < -1 || v->x > 1 || v->y < -1 || v->y > 1 || v->z < -1 || v->z > 1)
		return (1);
	len = vector_length(v);
	if (len - 1 > 1e-8)
		return (1);
	return (0);
}

int	process_a(char **inf, t_tscene *tscene)
{
	if (!inf[1] || !inf[2] || inf[3])
		return (1);
	if (tscene->is_a_set == true)
		clean_exit("Error multiple Ambient light");
	tscene->ambient.ratio = ft_atof(inf[1]);
	if (!parse_rgb(inf[2], &tscene->ambient.color)
		|| tscene->ambient.ratio < 0 || tscene->ambient.ratio > 1)
		return (1);
	tscene->is_a_set = true;
	return (0);
}

int	ft_contain_virg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			return (1);
		i++;
	}
	return (0);
}

int	process_c(char **inf, t_tscene *t_scene)
{
	t_vector	normalized_dir;

	if (!inf[1] || !inf[2] || !inf[3] || inf[4])
		return (1);
	if (t_scene->is_c_set == true)
		clean_exit("Error multiple Cameras");
	t_scene->camera.fov = ft_atoi(inf[3]);
	if (ft_contain_virg(inf[3]))
		clean_exit("Error: Invalid Camera data");
	if (!parse_crd(inf[1], &t_scene->camera.position)
		|| !parse_crd(inf[2], &t_scene->camera.direction))
		return (1);
	if (t_scene->camera.fov > 180 || t_scene->camera.fov < 0
		|| is_norm(&t_scene->camera.direction))
		return (1);
	normalized_dir = vector_normalize(&t_scene->camera.direction);
	t_scene->camera.direction.x = normalized_dir.x;
	t_scene->camera.direction.y = normalized_dir.y;
	t_scene->camera.direction.z = normalized_dir.z;
	t_scene->is_c_set = true;
	return (0);
}

int	process_l(char **inf, t_tscene *t_scene)
{
	t_tlight	*new;

	if (!inf[1] || !inf[2] || !inf[3] || inf[4])
		return (1);
	new = new_light();
	new->bratio = ft_atof(inf[2]);
	if (!parse_crd(inf[1], &new->position)
		|| !parse_rgb(inf[3], &new->color)
		|| new->bratio < 0 || new->bratio > 1)
		return (1);
	light_add_front(&t_scene->light, new);
	t_scene->light_size++;
	return (0);
}
