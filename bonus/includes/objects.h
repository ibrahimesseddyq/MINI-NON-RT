/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:56:16 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/05 19:41:19 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECTS_H
# define OBJECTS_H

#include "defined.h"
#include "includes.h"
typedef t_vector t_point;


typedef struct s_color
{
    FLOAT r;
    FLOAT g;
    FLOAT b;
}t_color;
typedef struct s_ambient
{
    FLOAT ratio;
    t_color color;
} t_ambient;

typedef struct s_camera
{
    t_point position;
    t_vector direction;
    int   fov;
} t_camera;

typedef struct s_light
{
    t_point position;
    FLOAT bratio;
    t_color color;
} t_light;

typedef struct s_sphere
{
    t_point position;
    FLOAT diameter;
    t_color color;
    int id;
} t_sphere;

typedef struct s_plane
{
    t_point position;
    t_vector direction;
    t_color color;
     int id;
} t_plane;

typedef struct s_cylinder
{
    t_point position;
    t_vector direction;
    FLOAT diameter;
    FLOAT height;
    t_color color;
    int id;
} t_cylinder;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

typedef struct s_scene
{
    t_camera camera;
    t_light light;
    t_ambient ambient;
    t_data img;
    t_cylinder *cylinder;
    t_plane *plane;
    t_sphere *sphere;
    FLOAT viewport_width;
    FLOAT viewport_height;
    FLOAT height;
    FLOAT width;
    FLOAT viewport_dist;
    void *mlx;
    void *win;
    int plane_count;
    int cylinder_count;
    int sphere_count;
    
}t_scene;

typedef struct s_ray
{
    t_point origin;
    t_vector direction;
}t_ray;



#endif