#ifndef FNDEF_H
#define FNDEF_H
# include "includes.h"
# include "objects.h"
void draw(t_scene *scene);
int	pixel_color(t_scene *scene, t_intersection *isect, t_ray *ray);
int	count_args(const char **inf);
int	parse_material(const char *mat, t_material *material);
int	my_atoi(int *keys, int start);
void	rotate_point(t_point *p, t_vector axis, FLOAT angle);
bool	load_texture(t_texture *texture, void *mlx, char *filename);
void translate(int *keys, t_scene *scene);
void	rotate(int *keys, t_scene *scene);
void resize(int *keys, t_scene *scene);
void	move_light_or_camera(int *keys, t_scene *scene);
void	move_sphere(int *keys, t_sphere *sphere);
void	move_plane(int *keys, t_plane *plane);
void	move_cylinder(int *keys, t_cylinder *cylinder);
void	move_light(int *keys, t_light *light);
void	move_camera(int *keys, t_camera *camera);
bool	check_shadow(t_scene *scene, t_ray *ray, t_intersection *intersection);
void calculate_surface_properties(t_scene *scene, t_intersection *intersection, t_color *texture_color, t_vector *out_normal);
t_color	process_lights(t_scene *scene, t_intersection *isect,
	t_ray *ray, t_light_params *params);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
int	trace_ray(t_ray *ray, t_scene *scene);
#endif