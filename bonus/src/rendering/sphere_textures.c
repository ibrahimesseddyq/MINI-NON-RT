#include "./../../../minirt_bonus.h"

static t_color	get_sphere_texture_color(t_sphere *sphere,
	t_intersection *intersection)
{
	t_checker_config	checker;

	if (sphere->has_checkerboard)
	{
		checker = init_checker();
		return (get_checkerboard_color(checker.board1, checker.board2,
				intersection->u, intersection->v, checker.size));
	}
	if (sphere->texture_name)
		return (sample_texture(&sphere->texture,
				intersection->u, intersection->v));
	return ((t_color){0, 0, 0, 0});
}

static t_vector	calculate_sphere_normal(t_sphere *sphere,
	t_intersection *intersection)
{
	if (sphere->texture_name)
		return (calculate_bump_normal(&sphere->normal_texture,
				intersection->u, intersection->v,
				&intersection->normal));
	return (intersection->normal);
}

void	handle_sphere_maps(t_scene *scene, t_texture_params *params, int i)
{
	if (scene->sphere[i].has_color_texture)
	{
		*(params->texture_color) = get_sphere_texture_color(
				&scene->sphere[i], params->intersection);
	}
	else
		*(params->texture_color) = scene->sphere[i].color;
	if (scene->sphere[i].has_bump_texture)
		*(params->normal) = calculate_sphere_normal(
				&scene->sphere[i], params->intersection);
	*(params->set) = 1;
}

void	handle_sphere_textures(t_scene *scene, t_texture_params *params)
{
	int	i;

	i = -1;
	while (++i < scene->sphere_count)
	{
		if (params->intersection->id != scene->sphere[i].id)
		{
			i++;
			continue ;
		}
		if (scene->sphere[i].has_checkerboard || scene->sphere[i].texture_name)
			handle_sphere_maps(scene, params, i);
		break ;
	}
}
