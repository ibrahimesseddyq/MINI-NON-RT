/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:56:16 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/26 20:23:23 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OBJECTS_H
# define OBJECTS_H
# define ALT_KEY 65513
# define LEFT_ROW_KEY 65361
# define RIGHT_ROW_KEY 65363
# define UPPER_ROW_KEY 65362
# define DOWN_ROW_KEY 65364
# define ESC_KEY 65307
# define R_KEY 114
# define S_KEY 115
# define KEY_1 65436
# define KEY_2 65433
# define KEY_3 65435
# define KEY_4 65430
# define KEY_5 65437
# define KEY_6 65432
# define KEY_7 65429
# define KEY_8 65431
# define KEY_9 65434
# define KEY_X 120
# define KEY_Y 121
# define KEY_Z 122
# define KEY_MINUS 65453
# define KEY_PLUS 65451

# include "defined.h"
# include "includes.h"

typedef t_vector	t_point;

typedef struct s_color
{
	FLOAT	r;
	FLOAT	g;
	FLOAT	b;
}	t_color;
typedef struct s_ambient
{
	FLOAT	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_point		position;
	t_vector	direction;
	t_vector	up;
	t_vector	right;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_point	position;
	FLOAT	bratio;
	t_color	color;
}	t_light;

typedef struct s_sphere
{
	t_point		position;
	FLOAT		diameter;
	t_color		color;
	int			id;
}	t_sphere;

typedef struct s_plane
{
	t_point		position;
	t_vector	direction;
	t_color		color;
	int			id;
}	t_plane;

typedef struct s_cylinder
{
	t_point		position;
	t_vector	direction;
	FLOAT		diameter;
	FLOAT		height;
	FLOAT		checker_size;
	t_color		color;
	int			id;
}	t_cylinder;


typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_scene
{
	t_camera	camera;
	t_light		light;
	t_ambient	ambient;
	t_data		img;
	t_cylinder	*cylinder;
	t_plane		*plane;
	t_sphere	*sphere;
	FLOAT		viewport_width;
	FLOAT		viewport_height;
	FLOAT		height;
	FLOAT		width;
	FLOAT		viewport_dist;
	void		*mlx;
	void		*win;
	int			plane_count;
	int			cylinder_count;
	int			sphere_count;
}	t_scene;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_descriminant
{
	t_vector	oc;
	FLOAT		a;
	FLOAT		b;
	FLOAT		c;
	FLOAT		discriminant;
	FLOAT		t;
	FLOAT		t1;
	FLOAT		t2;
}	t_descriminant;

typedef struct s_cyhit
{
	FLOAT		body;
	t_vector	bottom_normal;
	FLOAT		bottom;
	t_vector	top_offset;
	t_point		top_center;
	FLOAT		top;
}	t_cyhit;

typedef struct s_caps
{
	t_ray		ray;
	t_cylinder cylinder;
	FLOAT		dmin;
}t_caps;

#endif