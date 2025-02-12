/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:09 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/12 18:43:36 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	set_vector_up(t_vector *up)
{
	up->x = 0;
	up->y = 1;
	up->z = 0;
}

void	draw_apixel(t_scene *scene, t_draw *draw_infos)
{
	draw_infos->pixel_x = (2 * ((draw_infos->x + 0.5) / WIDTH) - 1)
		* draw_infos->aspect_ratio * draw_infos->fov_scale;
	draw_infos->pixel_y = (1 - 2 * ((draw_infos->y + 0.5) / HEIGHT))
		* draw_infos->fov_scale;
	draw_infos->sclx = vector_scale(&draw_infos->right, draw_infos->pixel_x);
	draw_infos->scly = vector_scale(&draw_infos->up, draw_infos->pixel_y);
	draw_infos->add = vector_add(&draw_infos->sclx, &draw_infos->scly);
	draw_infos->direction = vector_add(&draw_infos->add, &draw_infos->forword);
	draw_infos->ray.origin = scene->camera.position;
	draw_infos->ray.direction = vector_normalize(&draw_infos->direction);
	my_mlx_pixel_put(&scene->img, draw_infos->x,
		draw_infos->y, trace_ray(&draw_infos->ray, scene));
}

void	draw(t_scene *scene)
{
	t_draw	draw_infos;

	draw_infos.aspect_ratio = (FLOAT)WIDTH / (FLOAT)HEIGHT;
	draw_infos.fov_scale = tan((scene->camera.fov * M_PI / 180.f) / 2);
	draw_infos.forword = vector_normalize(&scene->camera.direction);
	set_vector_up(&draw_infos.up);
	draw_infos.right = vector_cross(&draw_infos.forword, &draw_infos.up);
	draw_infos.up = vector_cross(&draw_infos.right, &draw_infos.forword);
	draw_infos.y = 0;
	while (draw_infos.y < HEIGHT)
	{
		draw_infos.x = 0;
		while (draw_infos.x < WIDTH)
		{
			draw_apixel(scene, &draw_infos);
			draw_infos.x++;
		}
		draw_infos.y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}
