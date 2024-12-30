/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:44:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/30 11:12:16 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"


void my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
FLOAT hip_spher(t_point *point, double radius, t_ray *ray)
{
    t_vector oc;
    FLOAT a;
    FLOAT b;
    FLOAT c;
    FLOAT discriminant;
    FLOAT t;

    oc = vector_sub(&ray->origin, point);
    a = vector_dot(&ray->direction, &ray->direction);
    b = -2.0 * vector_dot( &ray->direction,&oc);
    c = vector_dot(&oc, &oc) - radius * radius;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    t = (-b - sqrt(discriminant)) / (2.0 * a);
    
    return (t);  
}
int trace_ray(t_ray *ray, t_scene *scene)
{
    FLOAT t;
    t_intersection intersection;

    t = hip_spher(&scene->sphere[0].position, scene->sphere[0].diameter / 2, ray);
    intersection.hit = t > 0;
    if (intersection.hit)
    {
        t_vector scl = vector_scale(&ray->direction, t);
        intersection.point = vector_add(&ray->origin, &scl);
        t_vector normal = vector_sub(&intersection.point,&scene->sphere[0].position);
        // intersection.normal = vector_normalize(&normal);
        float ambient_r = (scene->ambient.color.r ) * scene->ambient.ratio ;
        float ambient_g = (scene->ambient.color.g ) * scene->ambient.ratio;
        float ambient_b = (scene->ambient.color.b ) * scene->ambient.ratio;
        t_vector light_dir = vector_sub(&intersection.point,&scene->light.position);
        float light_distance = sqrt(vector_dot(&light_dir, &light_dir));
        light_dir = vector_normalize(&light_dir);        
        FLOAT diff = fmax(0.0, vector_dot(&intersection.normal, &light_dir));
        float diffuse_r = (scene->light.color.r) * scene->light.bratio * diff;
        float diffuse_g = (scene->light.color.g) * scene->light.bratio * diff;
        float diffuse_b = (scene->light.color.b) * scene->light.bratio * diff;
        FLOAT red = (ambient_r + diffuse_r)* scene->sphere->color.r;
        FLOAT green = (ambient_g + diffuse_g) * scene->sphere->color.g;
        FLOAT blue = (ambient_b + diffuse_b) * scene->sphere->color.b;

        t_color final_color = {red, green, blue};
        return (colorToRgb(&final_color));
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
            direction = vector_add(&add,&forword );
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
    double time_taken;
   
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