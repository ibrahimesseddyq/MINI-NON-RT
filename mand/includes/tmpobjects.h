/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpobjects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:24:29 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/01 15:33:03 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef TMPOBJECTS_H
# define TMPOBJECTS_H

#include "includes.h"

typedef struct s_tsphere
{
    t_point position;
    FLOAT diameter;
    t_color color;
    struct s_tsphere *next;
}__attribute__((aligned(sizeof(FLOAT)))) t_tsphere;

typedef struct s_tplane
{
    t_point position;
    t_vector direction;
    t_color color;
    struct s_tplane *next;
}__attribute__((aligned(sizeof(FLOAT)))) t_tplane;

typedef struct s_tcylinder
{
    int  size; 
    t_point position;
    t_vector direction;
    FLOAT diameter;
    FLOAT height;
    t_color color;
    struct s_tcylinder *next;
}__attribute__((aligned(sizeof(FLOAT)))) t_tcylinder;

typedef struct s_tcone
{
    t_point vertex;
    t_vector axis;
    FLOAT angle;
    FLOAT height;
    t_color color;
    int id;
    struct s_tcone *next;
} t_tcone;
typedef struct s_tsceen
{
    t_camera camera;
    t_light light;
    t_ambient ambient;
    t_tcylinder *cylinder;
    t_tplane *plane;
    t_tsphere *sphere;
    int plane_size;
    int cylinder_size;
    int sphere_size;
    int cone_size;
    t_tcone *cone;
    bool is_c_set;
    bool is_l_set;
    bool is_a_set;
} t_tscene;

t_tsphere *new_sphere(void);
t_tcylinder *new_cylinder(void);
t_tplane *new_plane(void);
t_tcone *new_cone(void);

void  cylinder_add_front(t_tcylinder **cylinder, t_tcylinder *new);
void  plane_add_front(t_tplane **plane, t_tplane *new);
void  sphere_add_front(t_tsphere **sphere, t_tsphere *new);

#endif