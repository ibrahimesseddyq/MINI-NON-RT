/* ************************************************************************** */
/*			                                                                */
/*                                                        :::      ::::::::   */
/*   scene_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:11:36 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/26 10:55:27 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

int	process_sp(char **inf, t_tscene *t_scene)
{
	t_tsphere	*new;

	new = new_sphere();
	if (!inf[1] || !inf[2] || !inf[3] || inf[4])
		return (1);
	new->diameter = ft_atof(inf[2]);
	if (new->diameter < 0)
		clean_exit("Error: Sphere diameter can't be negative");
	if (!parse_crd(inf[1], &new->position)
		|| !parse_rgb(inf[3], &new->color))
		return (1);
	sphere_add_front(&t_scene->sphere, new);
	t_scene->sphere_size++;
	return (0);
}

int	process_pl(char **inf, t_tscene *t_scene)
{
	t_tplane	*new;

	new = new_plane();
	if (!inf[1] || !inf[2] || !inf[3] || inf[4])
		return (1);
	if (!parse_crd(inf[1], &new->position)
		|| !parse_crd(inf[2], &new->direction)
		|| !parse_rgb(inf[3], &new->color)
		|| new->direction.x < -1 || new->direction.x > 1
		|| new->direction.y < -1 || new->direction.y > 1
		|| new->direction.z < -1 || new->direction.z > 1)
		return (1);
	plane_add_front(&t_scene->plane, new);
	t_scene->plane_size++;
	return (0);
}

int	process_cy(char **inf, t_tscene *t_scene)
{
	t_tcylinder	*new;

	new = new_cylinder();
	if (!inf[1] || !inf[2] || !inf[3] || !inf[4] || !inf[5] || inf[6])
		return (1);
	new->diameter = ft_atof(inf[3]);
	new->height = ft_atof(inf[4]);
	if (new->diameter < 0 || new->height < 0)
		clean_exit("Error: Cylinder diameter or height can't be negative");
	if (!parse_crd(inf[1], &new->position)
		|| !parse_crd(inf[2], &new->direction)
		|| !parse_rgb(inf[5], &new->color)
		|| new->direction.x < -1 || new->direction.x > 1
		|| new->direction.y < -1 || new->direction.y > 1
		|| new->direction.z < -1 || new->direction.z > 1)
		return (1);
	cylinder_add_front(&t_scene->cylinder, new);
	t_scene->cylinder_size++;
	return (0);
}
