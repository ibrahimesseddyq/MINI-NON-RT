/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:44:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/25 13:07:52 by sessarhi         ###   ########.fr       */
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
int color (int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

int trace_ray(t_ray *ray, t_scene *scene)
{
    FLOAT t;
    t_intersection intersection;

    // Check intersection with the first sphere
    t = hip_spher(&scene->sphere[0].position, scene->sphere[0].diameter / 2, ray);
    intersection.hit = t > 0;
    if (intersection.hit)
    {
        t_vector scl = vector_scale(&ray->direction, t);
        intersection.distance = t;
        intersection.point = vector_add(&ray->origin, &scl);
        t_vector normal = vector_sub(&intersection.point, &scene->sphere[0].position);
        intersection.normal = vector_normalize(&normal);
        int r = (int)((intersection.normal.x + 1.0f) * 0.5f * 255) + scene->sphere[0].r;
        int g = (int)((intersection.normal.y + 1.0f) * 0.5f * 255) + scene->sphere[0].g;
        int b = (int)((intersection.normal.z + 1.0f) * 0.5f * 255) + scene->sphere[0].b;

        return color(r, g, b);
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

    aspect_ratio = (FLOAT)WIDTH / (FLOAT)HEIGHT;
    fov_scale = tan((scene->camera.fov * M_PI / 360) / 2);
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            pixel_x = (2 * ((x + 0.5) / WIDTH) - 1) * aspect_ratio * fov_scale;
            pixel_y = (1 - 2 * ((y + 0.5) / HEIGHT)) * fov_scale;
            direction.x = pixel_x;
            direction.y = pixel_y;
            direction.z = -1;
            ray = (t_ray){scene->camera.position, vector_normalize(&direction)};
            my_mlx_pixel_put(&scene->img, x, y, trace_ray(&ray, scene));
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}





void render(t_scene *scene)
{
   
    scene->mlx = mlx_init();
    scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "MiniRT");
    scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
    scene->img.addr = mlx_get_data_addr(scene->img.img,
         &scene->img.bits_per_pixel, &scene->img.line_length, &scene->img.endian);
    draw(scene);
    mlx_loop(scene->mlx);
    
}