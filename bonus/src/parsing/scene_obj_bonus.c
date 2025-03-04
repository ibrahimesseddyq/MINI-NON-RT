/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:11:36 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/20 11:23:27 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

int	process_sp(char **inf, t_tscene *t_scene)
{
	t_tsphere	*new;

	if (count_args((const char **)inf) != 7)
		clean_exit("Error: Sphere has wrong number of arguments");
	new = new_sphere();
	new->texture_name = ft_strdup(inf[5]);
	new->normal_texture_name = ft_strdup(inf[6]);
	new->has_color_texture = 1;
	new->has_bump_texture = 1;
	new->has_checkerboard = 0;
	if (!ft_strcmp(new->texture_name, "DEFAULT"))
		new->has_color_texture = 0;
	else if (!ft_strcmp(new->texture_name, "CHECK"))
		new->has_checkerboard = 1;
	if (!ft_strcmp(new->normal_texture_name, "DEFAULT"))
		new->has_bump_texture = 0;
	new->diameter = ft_atof(inf[2]);
	if (!parse_crd(inf[1], &new->position) || !parse_rgb(inf[3], &new->color)
		|| new->texture_name == NULL || new->diameter < 0
		|| !parse_material(inf[4], &new->material))
		clean_exit("Error: Sphere has wrong arguments");
	sphere_add_front(&t_scene->sphere, new);
	t_scene->sphere_size++;
	return (0);
}

int	process_pl(char **inf, t_tscene *t_scene)
{
	t_tplane	*new;

	if (count_args((const char **)inf) != 7)
		clean_exit("Error: Plane has wrong number of arguments");
	new = new_plane();
	new->texture_name = ft_strdup(inf[5]);
	new->normal_texture_name = ft_strdup(inf[6]);
	if (!ft_strcmp(new->texture_name, "DEFAULT"))
		new->has_color_texture = 0;
	else if (!ft_strcmp(new->texture_name, "CHECK"))
		new->has_checkerboard = 1;
	if (!ft_strcmp(new->normal_texture_name, "DEFAULT"))
		new->has_bump_texture = 0;
	if (!parse_crd(inf[1], &new->position) || !parse_crd(inf[2],
			&new->direction) || !parse_rgb(inf[3], &new->color)
		|| new->texture_name == NULL || new->direction.x < -1
		|| new->direction.x > 1 || new->direction.y < -1
		|| new->direction.y > 1 || new->direction.z < -1
		|| new->direction.z > 1 || !parse_material(inf[4], &new->material)
		|| vector_length(&new->direction) != 1)
		clean_exit("Error: Plane has wrong arguments");
	plane_add_front(&t_scene->plane, new);
	t_scene->plane_size++;
	return (0);
}

int	process_cy(char **inf, t_tscene *t_scene)
{
	t_tcylinder	*new;

	new = new_cylinder();
	if (count_args((const char **)inf) != 9)
		clean_exit("Error: Cylinder has wrong number of arguments");
	new->texture_name = ft_strdup(inf[7]);
	new->normal_texture_name = ft_strdup(inf[8]);
	if (!ft_strcmp(new->texture_name, "DEFAULT"))
		new->has_color_texture = 0;
	else if (!ft_strcmp(new->texture_name, "CHECK"))
		new->has_checkerboard = 1;
	if (!ft_strcmp(new->normal_texture_name, "DEFAULT"))
		new->has_bump_texture = 0;
	new->diameter = ft_atof(inf[3]);
	new->height = ft_atof(inf[4]);
	if (!parse_crd(inf[1], &new->position) || !parse_crd(inf[2],
			&new->direction) || !parse_rgb(inf[5], &new->color)
		|| new->diameter < 0 || new->height < 0
		|| !parse_material(inf[6], &new->material)
		|| is_norm(&new->direction))
		clean_exit("Error: Cylinder has wrong arguments");
	cylinder_add_front(&t_scene->cylinder, new);
	return (t_scene->cylinder_size++, 0);
}

int	process_co(char **inf, t_tscene *t_scene)
{
	t_tcone	*new;

	if (count_args((const char **)inf) != 9)
		clean_exit("Error: Cone has wrong number of arguments");
	new = new_cone();
	new->texture_name = ft_strdup(inf[7]);
	if (!ft_strcmp(new->texture_name, "DEFAULT"))
		new->has_color_texture = 0;
	else if (!ft_strcmp(new->texture_name, "CHECK"))
		new->has_checkerboard = 1;
	if (!ft_strcmp(new->normal_texture_name, "DEFAULT"))
		new->has_bump_texture = 0;
	new->angle = ft_atof(inf[3]);
	new->height = ft_atof(inf[4]);
	new->normal_texture_name = ft_strdup(inf[8]);
	if (!parse_crd(inf[1], &new->vertex) || !parse_crd(inf[2], &new->axis)
		|| !parse_rgb(inf[5], &new->color) || new->angle < 0
		|| new->height < 0 || !parse_material(inf[6], &new->material)
		|| is_norm(&new->axis))
		clean_exit("Error: Cone has wrong arguments");
	cone_add_front(&t_scene->cone, new);
	t_scene->cone_size++;
	return (0);
}
