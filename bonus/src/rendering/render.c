/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:44:32 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/13 15:16:41 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

bool	check_shadow(t_scene *scene, t_ray *ray, t_intersection *intersection)
{
	t_vector		tmp;
	t_intersection	shadow_intersection;
	FLOAT			d;

	tmp = vector_sub(&scene->light[0].position, &intersection->point);
	d = vector_length(&tmp);
	shadow_intersection.distance = d;
	shadow_intersection.hit = false;
	shadow_intersection.id = -1;
	shadow_intersection.hit
		= cone_intersection(scene, &shadow_intersection, ray);
	shadow_intersection.hit
		= sphere_intersection(scene, &shadow_intersection, ray);
	shadow_intersection.hit
		= cylinder_intersection(scene, &shadow_intersection, ray);
	shadow_intersection.hit
		= plane_intersection(scene, &shadow_intersection, ray);
	if (shadow_intersection.hit && intersection->id != shadow_intersection.id)
		return (true);
	return (false);
}

t_color	get_checkerboard_color(t_color color1,
		t_color color2, t_intersection *inter, FLOAT size)
{
	FLOAT	scaled_u;
	FLOAT	scaled_v;
	int		u_int;
	int		v_int;

	scaled_v = inter->v * size;
	scaled_u = inter->u * size;
	v_int = (int)floor(scaled_v);
	u_int = (int)floor(scaled_u);
	if ((u_int + v_int) % 2 == 0)
	{
		return (color1);
	}
	return (color2);
}

int	trace_ray(t_ray *ray, t_scene *scene)
{
	t_intersection	intersection;

	intersection.distance = INFINITY;
	intersection.hit = false;
	intersection.id = -1;
	intersection.hit = cone_intersection(scene, &intersection, ray);
	intersection.hit = sphere_intersection(scene, &intersection, ray);
	intersection.hit = cylinder_intersection(scene, &intersection, ray);
	intersection.hit = plane_intersection(scene, &intersection, ray);
	if (intersection.hit == true)
		return (pixel_color(scene, &intersection, ray));
	return (0x000000);
}

void	render(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "MiniRT");
	scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
			&scene->img.bits_per_pixel, &scene->img.line_length,
			&scene->img.endian);
	init_textures(scene);
	draw(scene);
	mlx_key_hook(scene->win, transformation, scene);
	mlx_hook(scene->win, 17, 0, hook, scene);
	mlx_loop(scene->mlx);
}
