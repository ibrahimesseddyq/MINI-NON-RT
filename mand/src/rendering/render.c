/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:44:32 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/19 20:06:39 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

void my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (int)(y * img->line_length + x * (img->bits_per_pixel * 0.125));
    *(unsigned int *)dst = color;
}

#define SHADOW_BIAS 0.0001f

bool check_shadow(t_scene *scene, t_ray *ray, t_intersection *intersection)
{
    int i;
    t_vector tmp;
    t_vector hit_point;
    t_vector to_original;
    t_vector scaled_dir;
    t_intersection shadow_intersection;
    FLOAT t;
    FLOAT d;

    tmp = vector_sub(&scene->light.position, &intersection->point);
    d = vector_length(&tmp);

    i = scene->sphere_count;
    while(i--)
    {
        if (scene->sphere[i].id == intersection->id)
            continue;
        t = hit_sphere(&scene->sphere[i].position, scene->sphere[i].diameter / 2.0, ray);
        if (t > EPSILON && t < d - EPSILON)
        {
            scaled_dir = vector_scale(&ray->direction, t);
            hit_point = vector_add(&ray->origin, &scaled_dir);
            to_original = vector_sub(&hit_point, &intersection->point);
            if (vector_length(&to_original) > SHADOW_BIAS)
                return (true);
        }
    }

    i = scene->cylinder_count;
    while(i--)
    {
        if (scene->cylinder[i].id == intersection->id)
            continue;
        t = hit_cylinder(&shadow_intersection, ray, &scene->cylinder[i], d);
        if (t > EPSILON && t < d - EPSILON)
        {
            scaled_dir = vector_scale(&ray->direction, t);
            hit_point = vector_add(&ray->origin, &scaled_dir);
            to_original = vector_sub(&hit_point, &intersection->point);
            if (vector_length(&to_original) > SHADOW_BIAS)
                return (true);
        }
    }

    i = scene->plane_count;
    while(i--)
    {
        if (scene->plane[i].id == intersection->id)
            continue;
        t = hit_plane(&scene->plane[i].position, &scene->plane[i].direction, ray);
        if (t > EPSILON && t < d - EPSILON)
        {
            scaled_dir = vector_scale(&ray->direction, t);
            hit_point = vector_add(&ray->origin, &scaled_dir);
            to_original = vector_sub(&hit_point, &intersection->point);
            if (vector_length(&to_original) > SHADOW_BIAS)
                return (true);
        }
    }
    return (false);
}

int pixel_color(t_scene *scene, t_intersection *intersection, t_ray *ray)
{
    t_color ambient;
    t_color diffuse;
    t_color final_color;
    t_vector light_dir;
    t_vector offset;
    t_vector ray_origin;
    t_ray shadow_ray;
    FLOAT diff;
    FLOAT offset_direction;

    bool is_inside = vector_dot(&intersection->normal, &ray->direction) > 0;
    offset_direction = is_inside ? -1.0 : 1.0;
    offset = vector_scale(&intersection->normal, SHADOW_BIAS * offset_direction);
    ray_origin = vector_add(&intersection->point, &offset);
    
    shadow_ray.origin = ray_origin;
    shadow_ray.direction = vector_sub(&scene->light.position, &ray_origin);
    shadow_ray.direction = vector_normalize(&shadow_ray.direction);

    if (check_shadow(scene, &shadow_ray, intersection))
        return 0x000000;

    ambient = color_scale(&scene->ambient.color, scene->ambient.ratio);
    light_dir = vector_sub(&scene->light.position, &intersection->point);
    light_dir = vector_normalize(&light_dir);
    diff = fmax(0.0, vector_dot(&intersection->normal, &light_dir));
    diffuse = color_scale(&scene->light.color, scene->light.bratio * diff);

    final_color = color_add(&ambient, &diffuse);
    final_color = color_mul(&final_color, &intersection->color);
    final_color.r = fmin(final_color.r, 1.0);
    final_color.g = fmin(final_color.g, 1.0);
    final_color.b = fmin(final_color.b, 1.0);

    return (colorToRgb(&final_color));
}
int trace_ray(t_ray *ray, t_scene *scene)
{
    t_intersection intersection;
    intersection.distance = INFINITY;
    intersection.hit = false;
    intersection.id = -1;
    intersection.hit = sphere_intersection(scene, &intersection, ray);
    intersection.hit = cylinder_intersection(scene, &intersection, ray);
    intersection.hit = plane_intersection(scene, &intersection, ray);
    if (intersection.hit == true)
        return (pixel_color(scene, &intersection, ray));
    return 0x000000;
}


void draw(t_scene *scene)
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

    aspect_ratio = (FLOAT)WIDTH / (FLOAT)HEIGHT;
    fov_scale = tan((scene->camera.fov * M_PI / 180.f) / 2);
    t_vector  forword = vector_normalize(&scene->camera.direction);
    t_vector up = {0, 1, 0};
    right = vector_cross(&forword,&up );
    up = vector_cross(&right, &forword);
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            pixel_x = (2 * ((x + 0.5) / WIDTH) - 1) * aspect_ratio * fov_scale;
            pixel_y = (1 - 2 * ((y + 0.5) / HEIGHT)) * fov_scale;
            t_vector sclx = vector_scale(&right, pixel_x);
            t_vector scly = vector_scale(&up, pixel_y);
            t_vector add = vector_add(&sclx, &scly);
            direction = vector_add(&add,&forword);
            ray.origin = scene->camera.position;
            ray.direction = vector_normalize(&direction);
            my_mlx_pixel_put(&scene->img, x, y, trace_ray(&ray, scene));
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}

int key_hook(int keycode, t_scene *scene)
{

    return (0);
}
int hook(t_scene *scene)
{
    mlx_destroy_window(scene->mlx, scene->win);
    exit(0);
    return (0);
}
char get_ascii(int key)
{
    if (key == KEY_1)
        return '1';
    else if (key == KEY_2)
        return '2';
    else if (key == KEY_3)
        return '3';
    else if (key == KEY_4)
        return '4';
    else if (key == KEY_5)
        return '5';
    else if (key == KEY_6)
        return '6';
    else if (key == KEY_7)
        return '7';
    else if (key == KEY_8)
        return '8';
    else if (key == KEY_9)
        return '9';
    else
        return '\0'; // Return a null character if no match is found.

}
int my_atoi(int *keys, int start)
{
    int i;
    char array[9] = {0};
    int array_index = 0;

    i = start; 
    while (i < 8)
    {
        char ascii = get_ascii(keys[i]);
        if (ascii == '\0')
            break;     
        array[array_index++] = ascii;
        i++;
    }
    array[array_index] = '\0';
    printf("atoi [%d]\n", array);
    return ft_atoi(array);
}

void rotate_point(t_point *p, t_vector axis, FLOAT angle)
{
    FLOAT cos_angle = cos(angle);
    FLOAT sin_angle = sin(angle);
    FLOAT dot = axis.x * p->x + axis.y * p->y + axis.z * p->z;
    t_point temp;

    temp.x = (cos_angle + (1 - cos_angle) * axis.x * axis.x) * p->x +
             ((1 - cos_angle) * axis.x * axis.y - axis.z * sin_angle) * p->y +
             ((1 - cos_angle) * axis.x * axis.z + axis.y * sin_angle) * p->z;

    temp.y = ((1 - cos_angle) * axis.y * axis.x + axis.z * sin_angle) * p->x +
             (cos_angle + (1 - cos_angle) * axis.y * axis.y) * p->y +
             ((1 - cos_angle) * axis.y * axis.z - axis.x * sin_angle) * p->z;

    temp.z = ((1 - cos_angle) * axis.z * axis.x - axis.y * sin_angle) * p->x +
             ((1 - cos_angle) * axis.z * axis.y + axis.x * sin_angle) * p->y +
             (cos_angle + (1 - cos_angle) * axis.z * axis.z) * p->z;

    p->x = temp.x;
    p->y = temp.y;
    p->z = temp.z;
}
void rotate(int *keys, t_scene *scene)
{
    int obj_id = my_atoi(keys, 2);
    printf("obj_id: [%d]\n", obj_id);
    if (obj_id == -1) 
        return;

    for (int i = 0; i < scene->cylinder_count; i++)
    {
        printf("cylinder id [%d]\n", scene->cylinder[i].id);
        if (scene->cylinder[i].id == obj_id)
        {
            // Assuming keys[1] holds the rotation axis (X, Y, or Z)
            t_vector axis = {0, 0, 0};  // Default (Z axis)
            FLOAT angle = M_PI / 4;     // Default rotation angle (45 degrees)

            if (keys[1] == KEY_X)
            {
                axis.x = 1;
            }
            else if (keys[1] == KEY_Y)
            {
                axis.y = 1;
            }
            else if (keys[1] == KEY_Z)
            {
                axis.z = 1;
            }

            rotate_point(&scene->cylinder[i].position, axis, angle);
            rotate_point((t_point *)&scene->cylinder[i].direction, axis, angle);
            return ; 
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
        cursor = 0;
        for(int i = 0;i < 10; i++)
        {
            keys[i] = 0;
        }
    }

    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(scene->mlx, scene->win);
        exit(0);
    }

    draw(scene);
    return 0;
}

void render(t_scene *scene)
{
    struct timeval start, end;
    FLOAT time_taken;
   
    scene->mlx = mlx_init();
    scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "MiniRT");
    scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
    scene->img.addr = mlx_get_data_addr(scene->img.img,
         &scene->img.bits_per_pixel, &scene->img.line_length, &scene->img.endian);
    gettimeofday(&start, NULL);
    draw(scene);
    gettimeofday(&end, NULL);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("Render time: %.6f seconds\n", time_taken);
    mlx_key_hook(scene->win, key_hook, scene);
    mlx_key_hook(scene->win, transformation, scene);
    mlx_hook(scene->win, 17, 0, hook, scene);
    mlx_loop(scene->mlx);
}
