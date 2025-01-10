/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:16:40 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/10 17:08:12 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "./includes/objects.h"
#include "./includes/tmpobjects.h"
#include "./includes/defined.h"
#include "./includes/math.h"
#include "./includes/memory.h"
#include "./includes/color.h"
#include "./includes/includes.h"

// Parsing
bool  parse_crd(const char *str, t_vector *vector);
bool	parse_rgb(const char *str ,t_color *color);


// Utils
char    **ft_split(char const *s, char c);
FLOAT	ft_atof(const char *str);
int	Rgb_value(const char *str);
void   process_flie( char **av , t_scene *scene);
void render(t_scene *scene);
int    ft_strcmp(const char *s1, const char *s2);
int    ft_atoi(const char *str);
bool plane_intersection(t_scene *scene, t_intersection *intersection, t_ray *ray);
bool sphere_intersection(t_scene *scene , t_intersection *intersection , t_ray *ray);
bool cylinder_intersection(t_scene *scene, t_intersection *intersection, t_ray *ray);
FLOAT hit_plane(t_vector *point, t_vector *normal, t_ray *ray);
#endif