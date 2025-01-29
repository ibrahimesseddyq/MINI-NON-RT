/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:06 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/01/28 22:24:07 by ibes-sed         ###   ########.fr       */
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
			load_texture(&scene->plane[i].texture, scene->mlx,
				scene->plane[i].texture_name);
		i++;
	}
	i = 0;
	while (i < scene->sphere_count)
	{
		if (scene->sphere[i].texture_name)
			load_texture(&scene->sphere[i].texture, scene->mlx,
				scene->sphere[i].texture_name);
		i++;
	}
	i = 0;
	while (i < scene->cylinder_count)
	{
		if (scene->cylinder[i].texture_name)
			load_texture(&scene->cylinder[i].texture, scene->mlx,
				scene->cylinder[i].texture_name);
		i++;
	}
	return ;
}

t_color	sample_texture(t_texture *texture, FLOAT u, FLOAT v)
{
	t_color	color;
	int		x;
	int		y;
	int		pixel;
	char	*dest;

	x = (int)(u * (texture->width - 1));
	y = (int)(v * (texture->height - 1));
	x = fmin(fmax(x, 0), texture->width - 1);
	y = fmin(fmax(y, 0), texture->height - 1);
	dest = texture->addr + (y * texture->line_length
			+ x * (texture->bits_per_pixel / 8));
	pixel = *(unsigned int *)dest;
	color.r = ((pixel & 0xFF0000) >> 16) / 255.0;
	color.g = ((pixel & 0x00FF00) >> 8) / 255.0;
	color.b = (pixel & 0x0000FF) / 255.0;
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
