/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:56:16 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/30 11:53:41 by ibes-sed         ###   ########.fr       */
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
# define M_KEY 109
# define N_KEY 110
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
# define KEY_Z 119
# define KEY_MINUS 65453
# define KEY_PLUS 65451
# include "defined.h"
# include "includes.h"

typedef t_vector	t_point;

typedef struct s_material
{
	FLOAT	ka;
	FLOAT	kd;
	FLOAT	ks;
	int		n;
}	t_material;

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

typedef struct s_texture
{
	void	*data;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_light
{
	t_point	position;
	FLOAT	bratio;
	t_color	color;
	int		id;
}	t_light;

typedef struct s_sphere
{
	t_point		position;
	FLOAT		diameter;
	t_texture	texture;
	t_texture	normal_texture;
	t_color		color;
	int			has_checkerboard;
	t_color		checker_color1;
	t_color		checker_color2;
	FLOAT		checker_size;
	char		*texture_name;
	char		*normal_texture_name;
	t_material	material;
	int			id;
}	t_sphere;

typedef struct s_plane
{
	t_point		position;
	t_vector	direction;
	t_texture	texture;
	t_texture	normal_texture;
	int			has_checkerboard;
	t_color		checker_color1;
	t_color		checker_color2;
	FLOAT		checker_size;
	char		*texture_name;
	char		*normal_texture_name;
	t_material	material;
	t_color		color;
	int			id;
}	t_plane;

typedef struct s_cylinder
{
	t_point		position;
	t_vector	direction;
	FLOAT		diameter;
	FLOAT		height;
	int			has_checkerboard;
	t_color		checker_color1;
	t_color		checker_color2;
	FLOAT		checker_size;
	t_texture	texture;
	t_texture	normal_texture;

	char		*texture_name;
	char		*normal_texture_name;

	t_color		color;
	t_material	material;
	int			id;
}	t_cylinder;

typedef struct s_cone
{
	t_point		vertex;
	t_vector	axis;
	FLOAT		angle;
	FLOAT		height;
	int			has_checkerboard;
	t_color		checker_color1;
	t_color		checker_color2;
	FLOAT		checker_size;
	char		*texture_name;
	char		*normal_texture_name;

	t_texture	texture;
	t_texture	normal_texture;

	t_material	material;
	t_color		color;
	int			id;
}	t_cone;

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
	t_ambient	ambient;
	t_data		img;
	t_cylinder	*cylinder;
	t_plane		*plane;
	t_sphere	*sphere;
	t_cone		*cone;
	t_light		*light;
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
	int			cone_count;
	int			light_count;
}	t_scene;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_cone_intersection
{
	t_vector cone_to_point;
	t_vector axis_scaled;
	t_vector subs_vec;
}	t_cone_intersection;

typedef struct t_hit_cone_intersection
{
	t_vector	oc;
	t_vector	scaled_v;
	t_vector	hit_point;
	t_vector	cone_to_hit;
	double		cos2;
	double		sin2;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t1;
	double		t2;
	double		t;
}	t_hit_cone_intersection;

typedef struct s_rotate_point
{
	FLOAT cos_angle;
	FLOAT sin_angle;
	FLOAT dot;

	FLOAT new_x;
	FLOAT new_y;
} t_rotate_point;

typedef struct s_bump_params
{
    FLOAT u;
    FLOAT v;
    FLOAT strength;
    t_texture *bump_map;
} t_bump_params;

typedef struct s_normal_modify
{
    t_vector *original_normal;
    t_vector *tangent;
    t_vector *bitangent;
    FLOAT dx;
    FLOAT dy;
} t_normal_modify;

typedef struct s_derivatives
{
    FLOAT dx;
    FLOAT dy;
} t_derivatives;

typedef struct s_light_params
{
    t_vector    surface_normal;
    t_vector    view_dir;
    t_vector    intersection_point;
    t_material  material;
}   t_light_params;

typedef struct s_light_calc
{
    t_color     diffuse;
    t_color     specular;
}   t_light_calc;

typedef struct s_body_intersection
{
	t_vector oc;
	FLOAT dir_dot_dir;
	FLOAT oc_dot_dir;
	FLOAT a;
	FLOAT b;
	FLOAT c;
	FLOAT discriminant;
	FLOAT sqrt_discriminant;
	FLOAT t1;
	FLOAT t2;
} t_body_intersection;

typedef struct s_body_hit_info
{
	t_vector scaled_dir;
	t_vector cp;
	FLOAT height;
	t_vector proj;
	t_vector radial;
	t_vector hit_point;
} t_body_hit_info;

typedef struct s_cap_intersection
{
	FLOAT t;
	t_vector scaled_dir;
	t_vector hit_point;
	t_vector cp;
	t_vector proj;
	t_vector radial;
} t_cap_intersection;

typedef struct s_hit_cy
{
	FLOAT		t_body;
	t_vector	bottom_normal;
	FLOAT		t_bottom;
	t_vector	top_offset;
	t_point		top_center;
	FLOAT		t_top;
} t_hit_cy;

typedef struct s_draw
{
    int x;
    int y;
    FLOAT pixel_x;
    FLOAT pixel_y;
    t_vector direction;
    t_ray ray;
    FLOAT aspect_ratio;
    FLOAT fov_scale;
    t_vector right;
    t_vector  forword;
    t_vector up;
    t_vector sclx;
    t_vector scly;
    t_vector add;
} t_draw;

typedef struct s_hit_sphere
{
	t_vector oc;
	FLOAT a;
	FLOAT b;
	FLOAT c;
	FLOAT discriminant;
	FLOAT t;
	FLOAT t1;
	FLOAT t2;
} t_hit_sphere_info;


#endif