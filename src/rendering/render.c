/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:44:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/25 16:53:08 by sessarhi         ###   ########.fr       */
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

// Helper function to check if a point is in shadow
bool is_in_shadow(t_scene *scene, t_vector *intersection_point, t_vector *light_dir)
{
    t_ray shadow_ray;
    FLOAT shadow_t;
    
    // Create a shadow ray from intersection point to light
    // Add a small offset to avoid self-intersection (bias)
    t_vector offset_point;
    FLOAT bias = 0.001f;
    offset_point.x = intersection_point->x + intersection_point->x * bias;
    offset_point.y = intersection_point->y + intersection_point->y * bias;
    offset_point.z = intersection_point->z + intersection_point->z * bias;
    
    shadow_ray.origin = offset_point;
    shadow_ray.direction = *light_dir;

    // Check intersection with all objects
    shadow_t = hip_spher(&scene->sphere[0].position, scene->sphere[0].diameter / 2, &shadow_ray);
    
    // If there's an intersection between the point and the light, the point is in shadow
    return (shadow_t > 0 && shadow_t < 1);
}

int trace_ray(t_ray *ray, t_scene *scene)
{
    FLOAT t;
    t_intersection intersection;

    t = hip_spher(&scene->sphere[0].position, scene->sphere[0].diameter / 2, ray);
    intersection.hit = t > 0;
    if (intersection.hit)
    {
        // Calculate intersection point and normal
        t_vector scl = vector_scale(&ray->direction, t);
        intersection.point = vector_add(&ray->origin, &scl);
        t_vector normal = vector_sub(&intersection.point, &scene->sphere[0].position);
        intersection.normal = vector_normalize(&normal);

        // Store original sphere color
        int sphere_r = scene->sphere[0].r;
        int sphere_g = scene->sphere[0].g;
        int sphere_b = scene->sphere[0].b;

        // Ambient lighting calculation
        float ambient_r = (scene->ambient.r * scene->ambient.ratio * sphere_r) / 255.0f;
        float ambient_g = (scene->ambient.g * scene->ambient.ratio * sphere_g) / 255.0f;
        float ambient_b = (scene->ambient.b * scene->ambient.ratio * sphere_b) / 255.0f;

        // Diffuse lighting calculation
        t_vector light_dir = vector_sub(&scene->light.position, &intersection.point);
        float light_distance = sqrt(vector_dot(&light_dir, &light_dir)); // Get light distance
        light_dir = vector_normalize(&light_dir);
        FLOAT diff = fmax(0.0, vector_dot(&intersection.normal, &light_dir));

        // Shadow calculation
        float shadow = 1.0f;
        if (is_in_shadow(scene, &intersection.point, &light_dir))
        {
            shadow = 0.0f; // Point is in complete shadow
        }

        // Apply shadow to diffuse lighting
        float diffuse_r = (scene->light.r * scene->light.bratio * diff * sphere_r * shadow) / 255.0f;
        float diffuse_g = (scene->light.g * scene->light.bratio * diff * sphere_g * shadow) / 255.0f;
        float diffuse_b = (scene->light.b * scene->light.bratio * diff * sphere_b * shadow) / 255.0f;

        // Light attenuation (optional)
        float attenuation = 1.0f / (1.0f + 0.01f * light_distance); // You can adjust these constants
        diffuse_r *= attenuation;
        diffuse_g *= attenuation;
        diffuse_b *= attenuation;

        // Combine lighting components
        int final_r = fmin((ambient_r + diffuse_r) * 255, 255);
        int final_g = fmin((ambient_g + diffuse_g) * 255, 255);
        int final_b = fmin((ambient_b + diffuse_b) * 255, 255);

        return color(final_r, final_g, final_b);
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
    fov_scale = tan((scene->camera.fov * M_PI / 180.f) / 2);
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            pixel_x = (2 * ((x + 0.5) / WIDTH) - 1) * aspect_ratio * fov_scale;
            pixel_y = (1 - 2 * ((y + 0.5) / HEIGHT)) * fov_scale;
            direction.x = pixel_x;
            direction.y = -pixel_y;
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