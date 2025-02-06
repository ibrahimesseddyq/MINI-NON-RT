/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:06 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/06 22:24:53 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION 
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

t_color	sample_texture(t_texture *texture, FLOAT u, FLOAT v)
{
	t_color			color;
	int				x;
	int				y;
	unsigned int	pixel;
	unsigned char	*pixel_ptr;

	u = u - floor(u);
	v = v - floor(v);
	x = (int)(u * (texture->width - 1));
	y = (int)(v * (texture->height - 1));
	x = fmin(fmax(x, 0), texture->width - 1);
	y = fmin(fmax(y, 0), texture->height - 1);
	if (!texture || !texture->addr)
		return ((t_color){0, 0, 0});
	pixel_ptr = (unsigned char *)(texture->addr
			+ (y * texture->line_length + x * (texture->bits_per_pixel / 8)));
	color.r = pixel_ptr[0] / 255.0f;
	color.g = pixel_ptr[1] / 255.0f;
	color.b = pixel_ptr[2] / 255.0f;
	return (color);
}

bool	load_texture(t_texture *texture, void *mlx, char *filename)
{
	int				width;
	int				height;
	int				channels;
	unsigned char	*image_data;

	image_data = stbi_load(filename, &width,
			&height, &channels, 4);
	if (!image_data)
		return (false);
	texture->data = mlx_new_image(mlx, width, height);
	if (!texture->data)
		return (false);
	texture->addr = mlx_get_data_addr(texture->data,
			&texture->bits_per_pixel,
			&texture->line_length,
			&texture->endian);
	if (!texture->addr)
		return (false);
	ft_memcpy(texture->addr, image_data, width * height * 4);
	texture->width = width;
	texture->height = height;
	return (true);
}
