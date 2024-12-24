/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:56:16 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/24 17:49:29 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECTS_H
# define OBJECTS_H
#include "defined.h"
typedef t_vector t_point;
#include "./../MLX/mlx.h"

typedef struct s_ambient
{
    FLOAT ratio;
    int r;
    int g;
    int b;
}__attribute__((aligned(sizeof(FLOAT)))) t_ambient;

typedef struct s_camera
{
    t_point position;
    t_vector direction;
    int   fov;
}__attribute__((aligned(sizeof(FLOAT)))) t_camera;

typedef struct s_light
{
    t_point position;
    FLOAT bratio;
    int r;
    int g;
    int b;
}__attribute__((aligned(sizeof(FLOAT)))) t_light;

typedef struct s_sphere
{
    t_point position;
    FLOAT diameter;
    int r;
    int g;
    int b;
}__attribute__((aligned(sizeof(FLOAT)))) t_sphere;

typedef struct s_plane
{
    t_point position;
    FLOAT vx;
    FLOAT vy;
    FLOAT vz;
    int r;
    int g;
    int b;
}__attribute__((aligned(sizeof(FLOAT)))) t_plane;

typedef struct s_cylinder
{
    t_point position;
    FLOAT vx;
    FLOAT vy;
    FLOAT vz;
    FLOAT diameter;
    FLOAT height;
    int r;
    int g;
    int b;
}__attribute__((aligned(sizeof(FLOAT)))) t_cylinder;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_scene
{
    t_camera camera;
    t_light light;
    t_ambient ambient;
    t_cylinder *cylinder;
    t_plane *plane;
    t_sphere *sphere;
    FLOAT viewport_width;
    FLOAT viewport_height;
    FLOAT height;
    FLOAT width;
    int plane_count;
    int cylinder_count;
    int sphere_count;
    FLOAT viewport_dist;
    void *mlx;
    void *win;
    t_data img;
    
} t_scene;

typedef struct s_ray
{
    t_point origin;
    t_vector direction;
} t_ray;


#endif