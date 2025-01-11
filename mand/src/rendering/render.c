/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:44:32 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/11 17:31:42 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

void my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (int)(y * img->line_length + x * (img->bits_per_pixel * 0.125));
    *(unsigned int *)dst = color;
}

bool check_shadow(t_scene *scene, t_ray *ray,t_intersection *intersection)
{
    int i;
    t_intersection shadow_intersection;
    t_vector tmp;
    FLOAT d;

    tmp = vector_sub(&scene->light.position, &intersection->point);
    d = vector_length(&tmp);
    shadow_intersection.distance = INFINITY;
    i = scene->sphere_count;
    while(i--)
    {
        if (sphere_intersection(scene, &shadow_intersection, ray) && 
        shadow_intersection.id != intersection->id
        && 
        shadow_intersection.distance < d)
            return (true);
    }
    shadow_intersection.distance = INFINITY;
    i = scene->cylinder_count;
    while(i--)
    {
        if (cylinder_intersection(scene, &shadow_intersection, ray) && 
        shadow_intersection.id != intersection->id && 
        shadow_intersection.distance < d)
            return (true);
    }
    shadow_intersection.distance = INFINITY;
    i = scene->plane_count;
    while(i--)
    {
        if (plane_intersection(scene, &shadow_intersection, ray) && 
        shadow_intersection.id != intersection->id&& 
        shadow_intersection.distance < d)
            return (true);
    }
    return (false);
}
int pixel_color(t_scene *scene , t_intersection *intersection, t_ray *ray)
{
    t_color ambient;
    t_color diffuse;
    t_color final_color;
    t_vector light_dir;
    FLOAT diff;
    t_ray shadow_ray;

    shadow_ray.origin = intersection->point;
    shadow_ray.direction = vector_sub(&scene->light.position, &intersection->point);
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
    mlx_loop(scene->mlx);
}
