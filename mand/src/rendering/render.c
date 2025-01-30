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

int	hook(t_scene *scene)
{
	mlx_destroy_window(scene->mlx, scene->win);
	clean_exit("");
	return (0);
}
char	get_ascii(int key)
{
	if (key == KEY_1)
		return ('1');
	else if (key == KEY_2)
		return ('2');
	else if (key == KEY_3)
		return ('3');
	else if (key == KEY_4)
		return ('4');
	else if (key == KEY_5)
		return ('5');
	else if (key == KEY_6)
		return ('6');
	else if (key == KEY_7)
		return ('7');
	else if (key == KEY_8)
		return ('8');
	else if (key == KEY_9)
		return ('9');
	else
		return ('\0');
}
int	my_atoi(int *keys, int start)
{
	int		i;
	char	array[9] = {0};
	int		array_index = 0;
	char	ascii;

	i = start;
	while (i < 8)
	{
		ascii = get_ascii(keys[i]);
		if (ascii == '\0')
			break ;
		array[array_index++] = ascii;
		i++;
	}
	array[array_index] = '\0';
	return (ft_atoi(array));
}

void	rotate_point(t_point *p, t_vector axis, FLOAT angle)
{
	FLOAT cos_angle = cos(angle);
	FLOAT sin_angle = sin(angle);
	FLOAT dot = axis.x * p->x + axis.y * p->y + axis.z * p->z;
	t_point temp;
	if (axis.x == 0 && axis.y == 0 && axis.z == 1)
	{
		FLOAT cos_angle = cos(angle);
		FLOAT sin_angle = sin(angle);
		
		// 2D rotation in XY plane
		FLOAT new_x = p->x * cos_angle - p->y * sin_angle;
		FLOAT new_y = p->x * sin_angle + p->y * cos_angle;
		
		p->x = new_x;
		p->y = new_y;
		// Z remains unchanged
		return;
	}
	temp.x = (cos_angle + (1 - cos_angle) * axis.x * axis.x) * p->x +
			 ((1 - cos_angle) * axis.x * axis.y - axis.z * sin_angle) * p->y +
			 ((1 - cos_angle) * axis.x * axis.z + axis.y * sin_angle) * p->z;

	temp.y = ((1 - cos_angle) * axis
	   .y * axis.x + axis.z * sin_angle) * p->x +
			 (cos_angle + (1 - cos_angle) * axis.y * axis.y) * p->y +
			 ((1 - cos_angle) * axis.y * axis.z - axis.x * sin_angle) * p->z;

	temp.z = ((1 - cos_angle) * axis.z * axis.x - axis.y * sin_angle) * p->x +
			 ((1 - cos_angle) * axis.z * axis.y + axis.x * sin_angle) * p->y +
			 (cos_angle + (1 - cos_angle) * axis.z * axis.z) * p->z;

	p->x = temp.x;
	p->y = temp.y;
	p->z = temp.z;
}
void resize(int *keys, t_scene *scene)
{
	int obj_id = my_atoi(keys, 2);
	FLOAT ratio;

	if (keys[1] == KEY_PLUS)
		ratio = 1.1;
	else if (keys[1] == KEY_MINUS)
		ratio = 0.9;

	printf("obj_id: [%d]\n", obj_id);
	if (obj_id == -1) 
		return;
	for( int i = 0; i < scene->sphere_count; i++)
	{
		if (scene->sphere[i].id == obj_id)
		{
			scene->sphere[i].diameter *= ratio;
		}
	}
	for (int i = 0; i < scene->cylinder_count; i++)
	{
		if (scene->cylinder[i].id == obj_id)
		{
			scene->cylinder[i].height *= ratio;
			scene->cylinder[i].diameter *= ratio;
		}
	}
	for (int i = 0; i < scene->plane_count; i++)
	{
		if (scene->plane[i].id == obj_id)
		{
			scene->plane[i].direction.x *= ratio;
			scene->plane[i].direction.y *= ratio;
			scene->plane[i].direction.z *= ratio;

		}
	}
}

void rotate(int *keys, t_scene *scene)
{
	int obj_id = my_atoi(keys, 2);
	if (obj_id == -1) 
		return;

	for (int i = 0; i < scene->cylinder_count; i++)
	{
		printf("0 direction x[%f] y[%f] z[%f]\n", scene->cylinder[i].direction);

		if (scene->cylinder[i].id == obj_id)
		{
			t_vector axis = {0, 0, 0};
			FLOAT angle = M_PI / 4;

			if (keys[1] == KEY_X)
				axis.x = 1;
			else if (keys[1] == KEY_Y)
				axis.y = 1;
			else if (keys[1] == KEY_Z)
				axis.z = 1;

			// Rotate position
			// rotate_point(&scene->cylinder[i].position, axis, angle);
			
			// Rotate direction, but ensure it remains a unit vector
			t_vector original_direction = scene->cylinder[i].direction;
			printf("direction x[%f] y[%f] z[%f]\n", original_direction);
			rotate_point((t_point *)&scene->cylinder[i].direction, axis, angle);
			printf("2 direction x[%f] y[%f] z[%f]\n", scene->cylinder[i].direction);

			// Normalize the direction to ensure it's a unit vector
			FLOAT length = sqrt(
				scene->cylinder[i].direction.x * scene->cylinder[i].direction.x +
				scene->cylinder[i].direction.y * scene->cylinder[i].direction.y +
				scene->cylinder[i].direction.z * scene->cylinder[i].direction.z
			);
			
			if (length > 0) {
				scene->cylinder[i].direction.x /= length;
				scene->cylinder[i].direction.y /= length;
				scene->cylinder[i].direction.z /= length;
			}

			return; 
		}
	}
}
void move_cylinder(int *keys, t_cylinder *cylinder)
{
	if (keys[0] == LEFT_ROW_KEY)
	{
		cylinder->position.x--;
	}
	else if (keys[0] == RIGHT_ROW_KEY)
	{
		cylinder->position.x++;
	}
	else if (keys[0] == UPPER_ROW_KEY)
	{
		cylinder->position.y++;
	}
	else if (keys[0] == DOWN_ROW_KEY)
	{
		cylinder->position.y--;
	}
}

void move_plane(int *keys, t_plane *plane)
{
	if (keys[0] == LEFT_ROW_KEY)
	{
		plane->position.x--;
	}
	else if (keys[0] == RIGHT_ROW_KEY)
	{
		plane->position.x++;
	}
	else if (keys[0] == UPPER_ROW_KEY)
	{
		plane->position.y++;
	}
	else if (keys[0] == DOWN_ROW_KEY)
	{
		plane->position.y--;
	}
}

void move_sphere(int *keys, t_sphere *sphere)
{
	if (keys[0] == LEFT_ROW_KEY)
	{
		sphere->position.x--;
	}
	else if (keys[0] == RIGHT_ROW_KEY)
	{
		sphere->position.x++;
	}
	else if (keys[0] == UPPER_ROW_KEY)
	{
		sphere->position.y++;
	}
	else if (keys[0] == DOWN_ROW_KEY)
	{
		sphere->position.y--;
	}
}

void translate(int *keys, t_scene *scene)
{
	int obj_id = my_atoi(keys, 1);
					 printf("obj_id: [%d]\n", obj_id);

	if (obj_id == -1) 
		return;

	for (int i = 0; i < scene->sphere_count; i++)
	{
		if (scene->sphere[i].id == obj_id)
		{
			move_sphere(keys, &scene->sphere[i]);
			return; 
		}
	}
	for (int i = 0; i < scene->cylinder_count; i++)
	{
		if (scene->cylinder[i].id == obj_id)
		{
			move_cylinder(keys, &scene->cylinder[i]);
			return; 
		}
	}
	for (int i = 0; i < scene->plane_count; i++)
	{
		if (scene->plane[i].id == obj_id)
		{
			move_plane(keys, &scene->plane[i]);
			return; 
		}
	}
}

int transformation(int keycode, t_scene *scene)
{
	static int keys[10] = {0};
	static int cursor = 0;

	printf("hi\n");
	if (cursor < 10) 
		keys[cursor++] = keycode;

	if (keycode == ALT_KEY)
	{
		printf("ALT_KEY\n");
		for(int i = 0;i < 10; i++)
		{
			printf("key [%d]\n",keys[i]);
		}
		if (keys[0] == LEFT_ROW_KEY || keys[0] == UPPER_ROW_KEY ||
			keys[0] == RIGHT_ROW_KEY || keys[0] == DOWN_ROW_KEY)
		{
					printf("Translate\n");

			translate(keys, scene);
		}
		else if (keys[0] == R_KEY)
		{
			rotate(keys, scene);
		}
		else if (keys[0] == S_KEY)
		{
			resize(keys, scene);
		}
		cursor = 0;
		for(int i = 0;i < 10; i++)
			keys[i] = 0;
	}

	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(scene->mlx, scene->win);
		exit(0);
	}
	draw(scene);
	return 0;
}

void	render(t_scene *scene)
{
	struct timeval	start;
	struct timeval	end;
	FLOAT			time_taken;

	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "MiniRT");
	scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
			&scene->img.bits_per_pixel,
			&scene->img.line_length, &scene->img.endian);
	gettimeofday(&start, NULL);
	draw(scene);
	gettimeofday(&end, NULL);
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
	printf("Render time: %.6f seconds\n", time_taken);
	mlx_key_hook(scene->win, transformation, scene);
	mlx_hook(scene->win, 17, 0, hook, scene);
	mlx_loop(scene->mlx);
}
