/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:11:36 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/23 13:48:39 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

int count_args(const char** inf)
{
    int arg_count;
    arg_count = 0;
    while (inf[arg_count] != NULL)
        arg_count++;
    return (arg_count);
}
int parse_material(const char *mat, t_material *material)
{
  char **tab;
  tab = ft_split(mat, ',');
    if (count_args(tab) != 4)
        clean_exit("Error: Material has wrong number of arguments");
    material->ka = ft_atof(tab[0]);
    material->kd = ft_atof(tab[1]);
    material->ks = ft_atof(tab[2]);
    material->n = ft_atoi(tab[3]);
    if (material->ka > 1 || material->kd > 1 || material->ks > 1
    || material->n < 0 || material->ka < 0 || material->kd < 0
    || material->ks < 0)
    clean_exit("Error: Material has wrong arguments");
    return (0);
}

int process_sp(char **inf, t_tscene *t_scene)
{
    t_tsphere *new;
    
    if (count_args(inf) != 6)
      clean_exit("Error: Sphere has wrong number of arguments");
    new = new_sphere();
    new->texture_name = strdup(inf[5]);
    new->diameter = ft_atof(inf[2]);
    if (!parse_crd(inf[1], &new->position) ||
        !parse_rgb(inf[3], &new->color) || new->texture_name == NULL)
    clean_exit("Error: Sphere has wrong arguments");
    parse_material(inf[4], &new->material);
    sphere_add_front(&t_scene->sphere, new);
    t_scene->sphere_size++;
    return (0);
}

int process_pl(char **inf, t_tscene *t_scene)
{
    t_tplane *new;
    if (count_args(inf) != 6)
        clean_exit("Error: Plane has wrong number of arguments");
    new = new_plane();
    new->texture_name = strdup(inf[5]);
    if (!parse_crd(inf[1], &new->position) ||
        !parse_crd(inf[2], &new->direction) ||
        !parse_rgb(inf[3], &new->color) || new->texture_name == NULL)
        clean_exit("Error: Plane has wrong arguments");
    parse_material(inf[4], &new->material);
    plane_add_front(&t_scene->plane, new);
    t_scene->plane_size++;
    return (0);
}

int process_cy(char **inf, t_tscene *t_scene)
{
    t_tcylinder *new;
    
    new = new_cylinder();
    if (count_args(inf) != 8)
        clean_exit("Error: Cylinder has wrong number of arguments");
    new->texture_name = strdup(inf[7]);
    new->diameter = ft_atof(inf[3]);
    new->height = ft_atof(inf[4]);
    if (!parse_crd(inf[1], &new->position) ||
        !parse_crd(inf[2], &new->direction) ||
        !parse_rgb(inf[5], &new->color))
        clean_exit("Error: Cylinder has wrong arguments");
    parse_material(inf[6], &new->material);
    cylinder_add_front(&t_scene->cylinder, new);
    t_scene->cylinder_size++;
    return (0);
}

int process_co(char **inf, t_tscene *t_scene)
{
    t_tcone *new;
   if (count_args(inf) != 8)
        clean_exit("Error: Cone has wrong number of arguments");
    new = new_cone();
    new->angle = ft_atof(inf[3]);
    new->height = ft_atof(inf[4]);
    new->texture_name = strdup(inf[7]);
    if (!parse_crd(inf[1], &new->vertex) ||
        !parse_crd(inf[2], &new->axis) ||
        !parse_rgb(inf[5], &new->color))
        clean_exit("Error: Cone has wrong arguments");
    parse_material(inf[6], &new->material);
    cone_add_front(&t_scene->cone, new);
    t_scene->cone_size++;
    return (0);
}