/* ************************************************************************** */
/*				                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:44:32 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/26 22:26:48 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (int)(y * img->line_length + x
			* (img->bits_per_pixel * 0.125));
	*(unsigned int *)dst = color;
}

int	trace_ray(t_ray *ray, t_scene *scene)
{
	t_intersection	intersection;

	intersection.distance = INFINITY;
	intersection.hit = false;
	intersection.id = -1;
	intersection.hit = sphere_intersection(scene, &intersection, ray);
	intersection.hit = cylinder_intersection(scene, &intersection, ray);
	intersection.hit = plane_intersection(scene, &intersection, ray);
	if (intersection.hit == true)
		return (pixel_color(scene, &intersection, ray));
	return (0x000000);
}

void	camera_setup(t_camera *camera)
{
	t_vector	tmp;

	camera->aspect_ratio = (FLOAT)WIDTH / (FLOAT)HEIGHT;
	camera->fov_scale = tan((camera->fov * M_PI / 180.f) / 2);
	if (camera->direction.x == 0 && camera->direction.y
		!= 0 && camera->direction.z == 0)
	{
		tmp.x = 0;
		tmp.y = 0;
		tmp.z = 1;
	}
	else
	{
		tmp.x = 0;
		tmp.y = 1;
		tmp.z = 0;
	}
	camera->right = vector_cross(&camera->direction, &tmp);
	camera->up = vector_cross(&camera->right, &camera->direction);
	camera->right = vector_normalize(&camera->right);
	camera->up = vector_normalize(&camera->up);
}

void	draw(t_scene *scene)
{
	int			x;
	int			y;
	int			i;
	t_camera	cam;
	t_ray		ray;

	i = -1;
	camera_setup(&scene->camera);
	cam = scene->camera;
	while (++i < HEIGHT * WIDTH)
	{
		x = i % WIDTH;
		y = i / WIDTH;
		cam.pixel_x = (2 * ((x + 0.5) / WIDTH) - 1)
			* cam.aspect_ratio * cam.fov_scale;
		cam.pixel_y = (1 - 2 * ((y + 0.5) / HEIGHT)) * cam.fov_scale;
		cam.sclx = vector_scale(&cam.right, cam.pixel_x);
		cam.scly = vector_scale(&cam.up, cam.pixel_y);
		cam.add = vector_add(&cam.sclx, &cam.scly);
		ray.direction = vector_add(&cam.add, &cam.direction);
		ray.origin = scene->camera.position;
		ray.direction = vector_normalize(&ray.direction);
		my_mlx_pixel_put(&scene->img, x, y, trace_ray(&ray, scene));
	}	
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}

void	render(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		clean_exit("Error mlx_init failed");
	scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "MiniRT");
	if (!scene->win)
		clean_exit("Error mlx_new_window failed");
	scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!scene->img.img)
	{
		mlx_destroy_window(scene->mlx, scene->win);
		clean_exit("Error mlx_new_image failed");
	}
	scene->img.addr = mlx_get_data_addr(scene->img.img,
			&scene->img.bits_per_pixel,
			&scene->img.line_length, &scene->img.endian);
	draw(scene);
	mlx_key_hook(scene->win, transformation, scene);
	mlx_hook(scene->win, 17, 0, hook, scene);
	mlx_loop(scene->mlx);
}
