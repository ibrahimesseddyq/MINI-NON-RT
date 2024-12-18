/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:56:16 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/18 11:28:24 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECTS_H
# define OBJECTS_H
#define FLOAT float // change this to double if you want to use double precision
typedef struct s_ambient
{
    FLOAT ratio;
    int r;
    int g;
    int b;
}__attribute__((aligned(sizeof(FLOAT)))) t_ambient;

typedef struct s_camera
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT vx;
    FLOAT vy;
    FLOAT vz;
    int   fov;
}__attribute__((aligned(sizeof(FLOAT)))) t_camera;

typedef struct s_light
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT bratio;
    int r;
    int g;
    int b;
}__attribute__((aligned(sizeof(FLOAT)))) t_light;

typedef struct s_sphere
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
    FLOAT diameter;
    int r;
    int g;
    int b;
}__attribute__((aligned(sizeof(FLOAT)))) t_sphere;

typedef struct s_plane
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
}__attribute__((aligned(sizeof(FLOAT)))) t_plane;

typedef struct s_cylinder
{
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
}__attribute__((aligned(sizeof(FLOAT)))) t_cylinder;

typedef struct s_vector
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
}__attribute__((aligned(sizeof(FLOAT)))) t_vector;

typedef struct s_ray
{
    t_vector origin;
    t_vector direction;
}__attribute__((aligned(sizeof(FLOAT)))) t_ray;

typedef struct t_intersection
{
    FLOAT t;
    t_vector point;
    t_vector normal;
    int r;
    int g;
    int b;
}__attribute__((aligned(sizeof(FLOAT)))) t_intersection;

typedef struct s_scene
{
    t_camera camera;
    t_light light;
    t_ambient alight;
    t_cylinder *cylinder;
    t_plane *plane;
    t_sphere *sphere;
} t_scene;


#endif