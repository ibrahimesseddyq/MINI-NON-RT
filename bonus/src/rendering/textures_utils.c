/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:06 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/14 20:28:01 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	init_textures(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->plane_count)
		if (scene->plane[i].texture_name)
			load_plane_texture(scene, i);
	i = -1;
	while (++i < scene->sphere_count)
		if (scene->sphere[i].texture_name)
			sphere_texture(scene, i);
	i = -1;
	while (++i < scene->cylinder_count)
		if (scene->cylinder[i].texture_name)
			cylinder_texture(scene, i);
	i = -1;
	while (++i < scene->cone_count)
		if (scene->cone[i].texture_name)
			cone_texture(scene, i);
}

void	setup_vector(t_color *vector, int switch_flag, unsigned char *pixel_ptr)
{
	if (switch_flag)
	{
		vector->r = pixel_ptr[2] * 0.003921569;
		vector->g = pixel_ptr[1] * 0.003921569;
		vector->b = pixel_ptr[0] * 0.003921569;
		return ;
	}
	vector->r = pixel_ptr[0] * 0.003921569;
	vector->g = pixel_ptr[1] * 0.003921569;
	vector->b = pixel_ptr[2] * 0.003921569;
}

t_color	sample_texture(t_texture *texture, FLOAT u, FLOAT v, int switch_flag)
{
	t_color			color;
	int				x;
	int				y;
	unsigned char	*pixel_ptr;

	u = u - floor(u);
	v = v - floor(v);
	pixel_ptr = NULL;
	color = (t_color){0, 0, 0};
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
	int	fd;

	if (!ft_strcmp(filename, "CHECK") || !ft_strcmp(filename, "DEFAULT"))
		return (true);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	else
		close(fd);
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
