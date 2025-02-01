/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:06 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/01/30 12:22:22 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#  define STB_IMAGE_IMPLEMENTATION
#include "./../../../minirt_bonus.h"
void	init_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->plane_count)
	{
		if (scene->plane[i].texture_name)
		{
			load_texture(&scene->plane[i].texture, scene->mlx,
				scene->plane[i].texture_name);
			load_texture(&scene->plane[i].normal_texture, scene->mlx, scene->plane[i].normal_texture_name);
		}

		i++;
	}
	i = 0;
	printf("count [%d]\n", scene->sphere_count);
	while (i < scene->sphere_count)
	{
		if (scene->sphere[i].texture_name)
		{
			load_texture(&scene->sphere[i].texture, scene->mlx,
				scene->sphere[i].texture_name);
			load_texture(&scene->sphere[i].normal_texture, scene->mlx, scene->sphere[i].normal_texture_name);

		}
		else
			printf("no textname\n");
		i++;
	}
	i = 0;
	while (i < scene->cylinder_count)
	{
		if (scene->cylinder[i].texture_name)
		{
			load_texture(&scene->cylinder[i].texture, scene->mlx,
				scene->cylinder[i].texture_name);
			load_texture(&scene->cylinder[i].normal_texture, scene->mlx, scene->cylinder[i].normal_texture_name);
		}
		i++;
	}
	printf("finish init\n");
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

// bool	load_texture(t_texture *texture, void *mlx, char *filename)
// {
// 	int	width;
// 	int	height;

// 	printf("texture  filename [%s]\n", filename);
// 	texture->data = mlx_xpm_file_to_image(mlx, filename, &width, &height);
// 	printf("didnt fail\n");
// 	if (!texture->data)
// 		return (exit(1), false);
// 	texture->width = width;
// 	texture->height = height;
// 	texture->addr = mlx_get_data_addr(texture->data,
// 			&texture->bits_per_pixel,
// 			&texture->line_length,
// 			&texture->endian);
// 	if (!texture->addr)
// 		return (false);
// 	return (true);
// }

bool load_texture(t_texture *texture, void *mlx, char *filename)
{
    int width, height, channels;
    
    printf("texture filename [%s]\n", filename);

    // Load the PNG image using stb_image
    unsigned char *image_data = stbi_load(filename, &width, &height, &channels, 4); // Force 4 channels (RGBA)
    if (!image_data)
    {
        printf("Failed to load texture [%s]\n", filename);
        return false;
    }

    // Create an image using MiniLibX
    texture->data = mlx_new_image(mlx, width, height);
    if (!texture->data)
    {
        // stbi_image_free(image_data);
        printf("Failed to create MLX image\n");
        return false;
    }

    // Get the image's address in memory
    texture->addr = mlx_get_data_addr(texture->data,
                                      &texture->bits_per_pixel,
                                      &texture->line_length,
                                      &texture->endian);
    if (!texture->addr)
    {
        // stbi_image_free(image_data);
        return false;
    }

    // Copy the loaded PNG data into the MLX image
    memcpy(texture->addr, image_data, width * height * 4); // RGBA is 4 bytes per pixel

    // Store width and height
    texture->width = width;
    texture->height = height;

    // Free the image data loaded by stb_image
    // stbi_image_free(image_data);

    return true;
}
