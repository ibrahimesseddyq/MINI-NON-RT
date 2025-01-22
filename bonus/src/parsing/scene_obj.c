/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:11:36 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/22 13:24:10 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

void cone_add_front(t_tcone **head, t_tcone *new);

// int process_sp(char **inf ,t_tscene *t_scene)
// {
//     t_tsphere *new;

//     new = new_sphere();
//     if (!inf[1] || !inf[2] || !inf[3] || inf[4])
//         return (1);
//     // if (inf[5])
//     // {
//     //     new->texture_name = strdup(inf[5]);
//     // }
//     new->diameter = ft_atof(inf[2]);
//     if (!parse_crd(inf[1],&new->position) ||
//         !parse_rgb(inf[3], &new->color) ||
//          new->diameter == (float)INT_MIN)
//             return (1);
//     sphere_add_front(&t_scene->sphere, new);
//     t_scene->sphere_size++;
//     return (0);
// }
int process_sp(char **inf, t_tscene *t_scene)
{
    t_tsphere *new;
    
    int arg_count = 0;
    while (inf[arg_count] != NULL)
        arg_count++;
        
    if (arg_count < 4) 
        return (1);
        
    new = new_sphere();
    if (!new)
        return (1);
        
    if (arg_count == 5)
    {
        new->texture_name = strdup(inf[4]);
        if (strcmp(new->texture_name, "CHECK") == 0)
        {
            new->has_checkerboard = true;
        }
        if (!new->texture_name)
        {
            free(new);
            return (1);
        }
    }
    
    new->diameter = ft_atof(inf[2]);
    if (!parse_crd(inf[1], &new->position) ||
        !parse_rgb(inf[3], &new->color) ||
        new->diameter == (float)INT_MIN)
    {
        if (new->texture_name)
            free(new->texture_name);
        free(new);
        return (1);
    }
    
    sphere_add_front(&t_scene->sphere, new);
    t_scene->sphere_size++;
    return (0);
}

int process_pl(char **inf, t_tscene *t_scene)
{
    t_tplane *new;
    int arg_count = 0;

    while (inf[arg_count] != NULL)
        arg_count++;

    if (arg_count < 4)  // Minimum required arguments
        return (1);

    new = new_plane();
    if (!new)
        return (1);

    // Handle optional texture
    if (arg_count == 5)  // Has texture
    {
        new->texture_name = strdup(inf[4]);
        if (strcmp(new->texture_name, "CHECK") == 0)
        {
            new->has_checkerboard = true;
        }
        if (!new->texture_name)
        {
            free(new);
            return (1);
        }
    }

    if (!parse_crd(inf[1], &new->position) ||
        !parse_crd(inf[2], &new->direction) ||
        !parse_rgb(inf[3], &new->color))
    {
        if (new->texture_name)
            free(new->texture_name);
        free(new);
        return (1);
    }

    plane_add_front(&t_scene->plane, new);
    t_scene->plane_size++;
    return (0);
}

int process_cy(char **inf, t_tscene *t_scene)
{
    t_tcylinder *new;
    int arg_count = 0;

    while (inf[arg_count] != NULL)
        arg_count++;

    if (arg_count < 6)  // Minimum required arguments
        return (1);

    new = new_cylinder();
    if (!new)
        return (1);

    // Handle optional texture
    if (arg_count == 7)  // Has texture
    {
        new->texture_name = strdup(inf[6]);
        if (strcmp(new->texture_name, "CHECK") == 0)
        {
            new->has_checkerboard = true;
        }
        if (!new->texture_name)
        {
            free(new);
            return (1);
        }
    }

    new->diameter = ft_atof(inf[3]);
    new->height = ft_atof(inf[4]);
    
    if (!parse_crd(inf[1], &new->position) ||
        !parse_crd(inf[2], &new->direction) ||
        !parse_rgb(inf[5], &new->color) ||
        new->diameter == (float)INT_MIN || 
        new->height == (float)INT_MIN)
    {
        if (new->texture_name)
            free(new->texture_name);
        free(new);
        return (1);
    }

    cylinder_add_front(&t_scene->cylinder, new);
    t_scene->cylinder_size++;
    return (0);
}

int process_co(char **inf, t_tscene *t_scene)
{
    t_tcone *new;
    int arg_count = 0;

    while (inf[arg_count] != NULL)
        arg_count++;

    if (arg_count < 6)  // Minimum required arguments
        return (1);

    new = new_cone();
    if (!new)
        return (1);

    // Handle optional texture
    if (arg_count == 7)  // Has texture
    {
        new->texture_name = strdup(inf[6]);
        if (strcmp(new->texture_name, "CHECK") == 0)
        {
            new->has_checkerboard = true;
        }
        if (!new->texture_name)
        {
            free(new);
            return (1);
        }
    }

    new->angle = ft_atof(inf[3]);
    new->height = ft_atof(inf[4]);

    if (!parse_crd(inf[1], &new->vertex) ||
        !parse_crd(inf[2], &new->axis) ||
        !parse_rgb(inf[5], &new->color) ||
        new->angle == (float)INT_MIN ||
        new->height == (float)INT_MIN)
    {
        if (new->texture_name)
            free(new->texture_name);
        free(new);
        return (1);
    }

    cone_add_front(&t_scene->cone, new);
    t_scene->cone_size++;
    return (0);
}