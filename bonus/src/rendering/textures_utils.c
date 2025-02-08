/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:06 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/08 18:07:02 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	init_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->plane_count)
	{
		if (scene->plane[i].texture_name)
			load_plane_texture(scene, i);
		i++;
	}
	i = 0;
	while (i < scene->sphere_count)
	{
		if (scene->sphere[i].texture_name)
			sphere_texture(scene, i);
		i++;
	}
	i = 0;
	while (i < scene->cylinder_count)
	{
		if (scene->cylinder[i].texture_name)
			cylinder_texture(scene, i);
		i++;
	}
	return ;
}

void	setup_vector(t_color *vector, int switch_flag, unsigned char *pixel_ptr)
{
	if (switch_flag)
	{
		vector->r = pixel_ptr[2] / 255.0f;
		vector->g = pixel_ptr[1] / 255.0f;
		vector->b = pixel_ptr[0] / 255.0f;
	}
	else
	{
		vector->r = pixel_ptr[0] / 255.0f;
		vector->g = pixel_ptr[1] / 255.0f;
		vector->b = pixel_ptr[2] / 255.0f;
	}
}

t_color	sample_texture(t_texture *texture, FLOAT u, FLOAT v, int switch_flag)
{
	t_color			color;
	int				x;
	int				y;
	unsigned int	pixel;
	unsigned char	*pixel_ptr;

	u = u - floor(u);
	v = v - floor(v);
	x = (int)((1.0 - u) * (texture->width - 1));
	y = (int)(v * (texture->height - 1));
	x = fmin(fmax(x, 0), texture->width - 1);
	y = fmin(fmax(y, 0), texture->height - 1);
	if (!texture || !texture->addr)
		return ((t_color){0, 0, 0});
	pixel_ptr = (unsigned char *)(texture->addr
			+ (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
	setup_vector(&color, switch_flag, pixel_ptr);
	return (color);
}

bool	load_texture(t_texture *texture, void *mlx, char *filename)
{
	int	width;
	int	height;

	texture->data = mlx_xpm_file_to_image(mlx, filename, &width, &height);
	if (!texture->data)
		return (false);
	texture->width = width;
	texture->height = height;
	texture->addr = mlx_get_data_addr(texture->data,
			&texture->bits_per_pixel,
			&texture->line_length,
			&texture->endian);
	if (!texture->addr)
		return (false);
	return (true);
}
