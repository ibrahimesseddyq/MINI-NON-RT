/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:53:30 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/25 22:39:18 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "./bonus/includes/objects.h"
# include "./bonus/includes/tmpobjects.h"
# include "./bonus/includes/defined.h"
# include "./bonus/includes/math.h"
# include "./bonus/includes/memory.h"
# include "./bonus/includes/color.h"
# include "./bonus/includes/includes.h"

bool    parse_crd(const char *str, t_vector *vector);
bool	parse_rgb(const char *str ,t_color *color);
char    **ft_split(char const *s, char c);
void    splil_line(const char *line , t_tscene *tscene);
FLOAT	ft_atof(const char *str);
int	Rgb_value(const char *str);
void   process_flie( char **av , t_scene *scene);
void render(t_scene *scene);
int    ft_strcmp(const char *s1, const char *s2);
int    ft_atoi(const char *str);
bool plane_intersection(const t_scene *scene, t_intersection *intersection,const t_ray *ray);
bool sphere_intersection(t_scene *scene , t_intersection *intersection , t_ray *ray);
bool cylinder_intersection(t_scene *scene, t_intersection *intersection, t_ray *ray);
int process_l(char **inf , t_tscene *t_scene);
int process_c(char **inf , t_tscene *t_scene);
int process_a(char **inf , t_tscene *tscene);
int process_sp(char **inf ,t_tscene *t_scene);
int process_pl(char **inf , t_tscene *t_scene);
int process_cy(char **inf , t_tscene *t_scene);
FLOAT hit_cylinder(t_intersection *intersection, const t_ray *ray, const t_cylinder *cylinder, FLOAT dmin);
FLOAT hit_sphere(t_point *point, double radius, t_ray *ray);
FLOAT hit_plane(const t_vector *point, const t_vector *normal, const t_ray *ray);
void copy_tscene(t_tscene *tscene, t_scene *scene);
void clean_exit(const char *msg);

#endif