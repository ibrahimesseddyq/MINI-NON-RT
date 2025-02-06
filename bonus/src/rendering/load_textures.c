#include "./../../../minirt_bonus.h"

void	load_plane_texture(t_scene *scene, int i)
{
	load_texture(&scene->plane[i].texture, scene->mlx,
		scene->plane[i].texture_name);
	load_texture(&scene->plane[i].normal_texture,
		scene->mlx, scene->plane[i].normal_texture_name);
}

void	sphere_texture(t_scene *scene, int i)
{
	load_texture(&scene->sphere[i].texture, scene->mlx,
		scene->sphere[i].texture_name);
	load_texture(&scene->sphere[i].normal_texture,
		scene->mlx, scene->sphere[i].normal_texture_name);
}

void	cylinder_texture(t_scene *scene, int i)
{
	load_texture(&scene->cylinder[i].texture, scene->mlx,
		scene->cylinder[i].texture_name);
	load_texture(&scene->cylinder[i].normal_texture,
		scene->mlx, scene->cylinder[i].normal_texture_name);
}
