/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:44:32 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/03 17:56:07 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"


void my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

FLOAT hit_cylinder(t_intersection *intersection, t_ray *ray, t_cylinder *cylinder)
{
    t_vector oc;
    FLOAT a;
    FLOAT b;
    FLOAT c;
    FLOAT discriminant;
    FLOAT t;
    
    oc = vector_sub(&ray->origin, &cylinder->position);
    a = vector_dot(&ray->direction, &ray->direction) - pow(vector_dot(&ray->direction, &cylinder->direction), 2);
    b = 2 * (vector_dot(&ray->direction, &oc) - vector_dot(&ray->direction, &cylinder->direction) * vector_dot(&oc, &cylinder->direction));
    c = vector_dot(&oc, &oc) - pow(vector_dot(&oc, &cylinder->direction), 2) - pow(cylinder->diameter / 2, 2);
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t < 0)
        return (-1);
    t_vector scl = vector_scale(&ray->direction, t);
    t_vector point = vector_add(&ray->origin, &scl);
    t_vector cp = vector_sub(&point, &cylinder->position);
    FLOAT height = vector_dot(&cp, &cylinder->direction);
    if (height < 0 || height > cylinder->height)
        return (-1);
    t_vector proj = vector_scale(&cylinder->direction, height);
    intersection->normal = vector_sub(&cp, &proj);
    return (t);
}
FLOAT hit_sphere(t_point *point, double radius, t_ray *ray)
{
    t_vector oc;
    FLOAT a;
    FLOAT b;
    FLOAT c;
    FLOAT discriminant;
    FLOAT t;
    oc = vector_sub(&ray->origin, point);
    a = vector_dot(&ray->direction, &ray->direction);
    b = 2.0 * vector_dot(&ray->direction,&oc);
    c = vector_dot(&oc, &oc) - radius * radius;
    discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0)
        return (-1);
    t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t > 0)
        return (t);
    t = (-b + sqrt(discriminant)) / (2.0 * a);
    return (t);  
}
FLOAT hit_plane(t_vector *point, t_vector *normal, t_ray *ray)
{
    FLOAT t;
    FLOAT denom;
    t_vector tmp;

    denom = vector_dot(normal, &ray->direction);
    if (fabs(denom) > 1e-6)
    {
        tmp = vector_sub(point, &ray->origin);
        t = vector_dot(&tmp, normal) / denom;
        if (t >= 0)
            return (t);
    }
    return (-1);
}
bool sphere_intersection(t_scene *scene , t_intersection *intersection , t_ray *ray)
{
    int i;
    FLOAT t;
    t_vector tmp;
    
    i = scene->sphere_count;
    while (i--)
    {
        tmp = vector_normalize(&scene->sphere[i].position);
        t = hit_sphere(&tmp, scene->sphere[i].diameter / 2.0, ray);
        if (t > 0 && t < intersection->distance)
        {
            intersection->hit = true;
            intersection->id = scene->sphere[i].id;
            intersection->distance = t;
            //(sessarhi note) the following three lines can be moved out f the loop for optimization
            intersection->color = scene->sphere[i].color;
            // tmp = vector_scale(&ray->direction, t);
    
        }
    }
    return (intersection->hit);
}
bool cylinder_intersection(t_scene *scene, t_intersection *intersection, t_ray *ray)
{
    int i;
    FLOAT t;
    t_vector tmp;
    
    i = scene->cylinder_count;
    while (i--)
    {
        t = hit_cylinder(intersection, ray, &scene->cylinder[i]);
        if (t > 0 && t < intersection->distance)
        {
            intersection->hit = true;
            intersection->id = scene->cylinder[i].id;
            intersection->distance = t;
            //(sessarhi note) the following three lines can be moved out f the loop for optimization
            intersection->color = scene->cylinder[i].color;
            intersection->normal = vector_normalize(&intersection->normal);
        }
    }
    return (intersection->hit);
}
bool plane_intersection(t_scene *scene, t_intersection *intersection, t_ray *ray)
{
    int i;
    FLOAT t;
    t_vector tmp;
    
    i = scene->plane_count;
    while (i--)
    {
        t = hit_plane(&scene->plane[i].position, &scene->plane[i].direction, ray);
        if (t > 0 && t < intersection->distance)
        {
            intersection->hit = true;
            intersection->id = scene->plane[i].id;
            intersection->distance = t;
            //(sessarhi note) the following three lines can be moved out f the loop for optimization
            intersection->color = scene->plane[i].color;
            intersection->normal = scene->plane[i].direction;
        }
    }
    return (intersection->hit);
}

int trace_ray(t_ray *ray, t_scene *scene)
{
    t_intersection intersection;
    intersection.distance = INFINITY;
    intersection.hit = false;
    intersection.hit = sphere_intersection(scene, &intersection, ray);
    intersection.hit = cylinder_intersection(scene, &intersection, ray);
    intersection.hit = plane_intersection(scene, &intersection, ray);
    if (intersection.hit == true)
    {
        return (colorToRgb(&intersection.color));
    }
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