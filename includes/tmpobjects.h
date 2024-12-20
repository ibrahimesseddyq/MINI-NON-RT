/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpobjects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:24:29 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/19 19:57:40 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef TMPOBJECTS_H
# define TMPOBJECTS_H

#include "objects.h"
#include "base.h"
typedef struct s_tsphere
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT diameter;
    int r;
    int g;
    int b;
    struct s_tsphere *next;
}__attribute__((aligned(sizeof(FLOAT)))) t_tsphere;

typedef struct s_tplane
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT vx;
    FLOAT vy;
    FLOAT vz;
    int r;
    int g;
    int b;
    struct s_tplane *next;
}__attribute__((aligned(sizeof(FLOAT)))) t_tplane;

typedef struct s_tcylinder
{
    int  size; 
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT vx;
    FLOAT vy;
    FLOAT vz;
    FLOAT diameter;
    FLOAT height;
    int r;
    int g;
    int b;
    struct s_tcylinder *next;
}__attribute__((aligned(sizeof(FLOAT)))) t_tcylinder;

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
    bool is_c_set;
    bool is_l_set;
    bool is_a_set;
} t_tscene;

t_tsphere *new_sphere(void);
t_tcylinder *new_cylinder(void);
t_tplane *new_plane(void);
void  cylinder_add_front(t_tcylinder **cylinder, t_tcylinder *new);
void  plane_add_front(t_tplane **plane, t_tplane *new);
void  sphere_add_front(t_tsphere **sphere, t_tsphere *new);

#endif