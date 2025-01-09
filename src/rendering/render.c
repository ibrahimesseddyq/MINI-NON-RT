/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:44:32 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/09 15:59:30 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

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
    t_vector proj;
    
    oc = vector_sub(&ray->origin, &cylinder->position);
    a = vector_dot(&ray->direction, &ray->direction) - pow(vector_dot(&ray->direction, &cylinder->direction), 2);
    b = 2 * (vector_dot(&ray->direction, &oc) - vector_dot(&ray->direction, &cylinder->direction) * vector_dot(&oc, &cylinder->direction));
    c = vector_dot(&oc, &oc) - pow(vector_dot(&oc, &cylinder->direction), 2) - pow(cylinder->diameter / 2, 2);
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t < 0)
    t = (-b + sqrt(discriminant)) / (2.0 * a);
    t_vector scl = vector_scale(&ray->direction, t);
    t_vector point = vector_add(&ray->origin, &scl);
    t_vector cp = vector_sub(&point, &cylinder->position);
    FLOAT height = vector_dot(&cp, &cylinder->direction);
    if (height >= 0 && height <= cylinder->height)
    {
        proj = vector_scale(&cylinder->direction, height);
        proj = vector_sub(&cp, &proj);
        intersection->normal = vector_normalize(&proj);
        return (t);
    }
    t_vector tmp =  vector_scale(&cylinder->direction, cylinder->height);
    t_point top = vector_add(&cylinder->position,&tmp);
    t = hit_plane(&cylinder->position, &cylinder->direction, ray);
    scl = vector_scale(&ray->direction, t);
    point = vector_add(&ray->origin, &scl);
    cp = vector_sub(&point,&cylinder->position);
    height = vector_dot(&cp, &cylinder->direction);
    if (height <= cylinder->diameter/2 )
    {
        intersection->normal = cylinder->direction;
        return (t);
    }
    t = hit_plane(&top, &cylinder->direction, ray);
    scl = vector_scale(&ray->direction, t);
    point = vector_add(&ray->origin, &scl);
    cp = vector_sub(&point, &top);
    height = vector_dot(&cp, &cylinder->direction);
    if (height <= cylinder->diameter/2 )
    {
        intersection->normal = cylinder->direction;
        return (t);
    }
    return (-1);
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
    discriminant = b * b - 4 * a * c;
if (discriminant < 0)
    return -1;

    FLOAT t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    FLOAT t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    if (t1 > 0 && t2 > 0)
        t = fmin(t1, t2);
    else if (t1 > 0)
        t = t1;
    else if (t2 > 0)
        t = t2;
    else
        return -1;
}

bool sphere_intersection(t_scene *scene , t_intersection *intersection , t_ray *ray)
{
    int i;
    FLOAT t;
    t_vector tmp;
    
    i = scene->sphere_count;
    while (i--)
    {
        t = hit_sphere(&scene->sphere[i].position, scene->sphere[i].diameter / 2.0, ray);
        if (t > 0 && t < intersection->distance)
        {
            intersection->hit = true;
            intersection->id = scene->sphere[i].id;
            intersection->distance = t;
            //(sessarhi note) the following three lines can be moved out f the loop for optimization
            intersection->color = scene->sphere[i].color;
            tmp = vector_scale(&ray->direction, t);
            intersection->point = vector_add(&ray->origin, &tmp);
            intersection->normal = vector_sub(&intersection->point, &scene->sphere[i].position);
            intersection->normal = vector_normalize(&intersection->normal);
    
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
            tmp = vector_scale(&ray->direction, t);
            intersection->point = vector_add(&ray->origin, &tmp);
        }
    }
    return (intersection->hit);
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
    {
        return (pixel_color(scene, &intersection, ray));
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