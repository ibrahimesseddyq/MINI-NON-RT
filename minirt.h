/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:16:40 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/20 10:55:58 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./mand/includes/objects.h"
# include "./mand/includes/tmpobjects.h"
# include "./mand/includes/defined.h"
# include "./mand/includes/math.h"
# include "./mand/includes/memory.h"
# include "./mand/includes/color.h"
# include "./mand/includes/includes.h"

bool	parse_crd(const char *str, t_vector *vector);
bool	parse_rgb(const char *str, t_color *color);
char	**ft_split(char const *s, char c);
FLOAT	ft_atof(const char *str);
int		rgb_value(const char *str);
void	process_flie( char **av, t_scene *scene);
void	render(t_scene *scene);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
bool	plane_intersection(const t_scene *scene,
			t_intersection *intersection, const t_ray *ray);
bool	sphere_intersection(t_scene *scene,
			t_intersection *intersection, t_ray *ray);
bool	cylinder_intersection(t_scene *scene,
			t_intersection *intersection, t_ray *ray);
int		process_l(char **inf, t_tscene *t_scene);
int		process_c(char **inf, t_tscene *t_scene);
int		process_a(char **inf, t_tscene *tscene);
int		process_sp(char **inf, t_tscene *t_scene);
int		process_pl(char **inf, t_tscene *t_scene);
int		process_cy(char **inf, t_tscene *t_scene);
FLOAT	hit_plane(const t_vector *point,
			const t_vector *normal, const t_ray *ray);
void	copy_tscene(t_tscene *tscene, t_scene *scene);
void	splil_line(const char *line, t_tscene *tscene);
void	clean_exit(const char *msg);
FLOAT	hit_cylinder(t_intersection *intersection, const t_ray *ray,
			const t_cylinder *cylinder, FLOAT dmin);
int		pixel_color(t_scene *scene, t_intersection *intersection, t_ray *ray);
void	move_light_or_camera(int *keys, t_scene *scene);
void	move_camera(int *keys, t_camera *camera);
void	move_light(int *keys, t_light *light);
void	move_cylinder(int *keys, t_cylinder *cylinder);
void	move_plane(int *keys, t_plane *plane);
void	move_sphere(int *keys, t_sphere *sphere);
void	rotate_point_z(t_point *p, t_rotate_point *rp, FLOAT angle);
void	rotate_point(t_point *p, t_vector axis, FLOAT angle);
void	set_axis(int *keys, t_vector *axis);
void	rotate_camera(int *keys, t_scene *scene);
void	rotate_cylinder(int *keys, t_scene *scene, int i);
void	rotate_plane(int *keys, t_scene *scene, int i);
void	rotate(int *keys, t_scene *scene);
int		transformation(int keycode, t_scene *scene);
int		search_and_translate(int *keys, int obj_id, t_scene *scene);
void	translate(int *keys, t_scene *scene);
void	search_and_resize(int obj_id, t_scene *scene, FLOAT ratio);
void	resize(int *keys, t_scene *scene);
char	get_ascii(int key);
int		my_atoi(int *keys, int start);
int		hook(t_scene *scene);
void	draw(t_scene *scene);
int		is_norm(t_vector *v);
#endif