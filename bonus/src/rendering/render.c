/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:44:32 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/24 11:03:24 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"


void my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
    char *dst;
    dst = img->addr + (int)(y * img->line_length + x * (img->bits_per_pixel * 0.125));
    *(unsigned int *)dst = color;
}

bool check_shadow(t_scene *scene, t_ray *ray, t_intersection *intersection)
{
    t_vector tmp;
    t_intersection shadow_intersection;
    FLOAT d;

    tmp = vector_sub(&scene->light[0].position, &intersection->point);
    d = vector_length(&tmp);
    shadow_intersection.distance = d;
    shadow_intersection.hit = false;
    shadow_intersection.id = -1;
    shadow_intersection.hit = sphere_intersection(scene, &shadow_intersection, ray);
    shadow_intersection.hit = cylinder_intersection(scene, &shadow_intersection, ray);
    shadow_intersection.hit = plane_intersection(scene, &shadow_intersection, ray);
    if (shadow_intersection.hit && intersection->id != shadow_intersection.id)
        return (true);
    return (false);
}
t_color sample_texture(t_texture *texture, FLOAT u, FLOAT v)
{
    t_color color;
    int x;
    int y;
    int pixel;
    char *dest;
    
    // Convert UV coordinates to pixel coordinates
    x = (int)(u * (texture->width - 1));
    y = (int)(v * (texture->height - 1));
    
    // Clamp coordinates
    x = fmin(fmax(x, 0), texture->width - 1);
    y = fmin(fmax(y, 0), texture->height - 1);
    
    // Get pixel from MLX image data
    dest = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    pixel = *(unsigned int *)dest;
    
    // Convert MLX color format (int) to RGB float values
    color.r = ((pixel & 0xFF0000) >> 16) / 255.0;
    color.g = ((pixel & 0x00FF00) >> 8) / 255.0;
    color.b = (pixel & 0x0000FF) / 255.0;
    
    return (color);
}
bool load_texture(t_texture *texture, void *mlx, char *filename)
{
    int width;
    int height;

    // Load XPM file
    texture->data = mlx_xpm_file_to_image(mlx, filename, &width, &height);
    if (!texture->data)
    {
        // printf("Failed to load texture: %s\n", filename);
        return false;
    }
    
    texture->width = width;
    texture->height = height;
    
    // Get image data address and properties
    texture->addr = mlx_get_data_addr(texture->data, 
                                     &texture->bits_per_pixel,
                                     &texture->line_length,
                                     &texture->endian);
    if (!texture->addr)
    {
        // printf("Failed to get texture data address for: %s\n", filename);
        return false;
    }

    // printf("Successfully loaded texture: %s (width: %d, height: %d)\n", 
        //    filename, width, height);
    return true;
}
t_vector calculate_bump_normal(t_texture *bump_map, FLOAT u, FLOAT v, t_vector *original_normal)
{
    t_color bump_sample;
    t_vector tangent, bitangent, modified_normal;
    FLOAT strength = 1.0;  // Adjust bump strength

    // Sample bump map
    if (!bump_map->addr)
        return *original_normal;

    // Sample neighboring points for gradient
    FLOAT step = 1.0 / bump_map->width;
    t_color c = sample_texture(bump_map, u, v);
    t_color cx = sample_texture(bump_map, u + step, v);
    t_color cy = sample_texture(bump_map, u, v + step);
    
    // Calculate height gradients
    FLOAT dx = (cx.r - c.r) * strength;
    FLOAT dy = (cy.r - c.r) * strength;

    // Calculate tangent and bitangent vectors
    // These should be perpendicular to the normal
    if (fabs(original_normal->y) < 0.99)
        tangent = vector_cross(original_normal, &(t_vector){0, 1, 0});
    else
        tangent = vector_cross(original_normal, &(t_vector){1, 0, 0});
    tangent = vector_normalize(&tangent);
    bitangent = vector_cross(&tangent, original_normal);
    bitangent = vector_normalize(&bitangent);

    // Modify normal based on bump map gradients
    modified_normal = *original_normal;
    t_vector scaled_tan = vector_scale(&tangent, dx);
    modified_normal = vector_add(&modified_normal, 
                               &scaled_tan);
    t_vector scaled_bitan = vector_scale(&bitangent, dy);

    modified_normal = vector_add(&modified_normal, 
                               &scaled_bitan);
    modified_normal = vector_normalize(&modified_normal);

    return modified_normal;
}
t_color get_checkerboard_color(t_color color1, t_color color2, FLOAT u, FLOAT v, FLOAT size)
{
    FLOAT scaled_u = u * size;
    FLOAT scaled_v = v * size;
    
    int u_int = (int)floor(scaled_u);
    int v_int = (int)floor(scaled_v);
    
    if ((u_int + v_int) % 2 == 0)
        return color1;
    return color2;
}
void calculate_surface_properties(t_scene *scene, t_intersection *intersection, t_color *texture_color, t_vector *out_normal)
{
    t_vector normal = intersection->normal;
    t_color checker_board1 = {0,0,0};
    t_color checker_board2 = {255, 255, 255};
    int checker_size = 4;
    int set;

    set = 0;
    for (int i = 0; i < scene->plane_count; i++)
    {
        if (intersection->id == scene->plane[i].id)
        {
            if (scene->plane[i].has_checkerboard)
            {
                *texture_color = get_checkerboard_color(
                    checker_board1,
                    checker_board2,
                    intersection->u,
                    intersection->v,
                    checker_size
                );
                set = 1;
            }
            else if (scene->plane[i].texture_name)
            {
                *texture_color = sample_texture(&scene->plane[i].texture, intersection->u, intersection->v);
                normal = calculate_bump_normal(&scene->plane[i].texture,
                                                 intersection->u, intersection->v,
                                                 &intersection->normal);
                set = 1;
            }
        }
    }
    for (int i = 0; i < scene->sphere_count; i++)
    {
        if (intersection->id == scene->sphere[i].id)
        {
            if (scene->sphere[i].has_checkerboard)
            {
                *texture_color = get_checkerboard_color(
                    checker_board1,
                    checker_board2,
                    intersection->u,
                    intersection->v,
                    checker_size
                );
                set = 1;
            }
            else if (scene->sphere[i].texture_name)
            {
                *texture_color = sample_texture(&scene->sphere[i].texture, intersection->u, intersection->v);
                normal = calculate_bump_normal(&scene->sphere[i].texture,
                                                 intersection->u, intersection->v,
                                                 &intersection->normal);
                set = 1;
            }
        }
    }
    for (int i = 0; i < scene->cylinder_count; i++)
    {
        if (intersection->id == scene->cylinder[i].id)
        {
            if (scene->cylinder[i].has_checkerboard)
            {
                *texture_color = get_checkerboard_color(
                    checker_board1,
                    checker_board2,
                    intersection->u,
                    intersection->v,
                    checker_size
                );
                set = 1;
            }
            else if (scene->cylinder[i].texture_name)
            {
                *texture_color = sample_texture(&scene->cylinder[i].texture, intersection->u, intersection->v);
                normal = calculate_bump_normal(&scene->cylinder[i].texture,
                                                 intersection->u, intersection->v,
                                                 &intersection->normal);
                set = 1;
            }
        }
    }
    if (!set)
    {
        *texture_color = intersection->color;
    }
    *out_normal = normal;
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
    t_vector surface_normal;

    bool is_inside = vector_dot(&intersection->normal, &ray->direction) > 0;
    offset_direction = is_inside ? -1.0 : 1.0;
    offset = vector_scale(&intersection->normal, SHADOW_BIAS * offset_direction);
    ray_origin = vector_add(&intersection->point, &offset);
    
    shadow_ray.origin = ray_origin;
    shadow_ray.direction = vector_sub(&scene->light[0].position, &ray_origin);
    shadow_ray.direction = vector_normalize(&shadow_ray.direction);
    if (check_shadow(scene, &shadow_ray, intersection))
        return 0x000000;

    // Instead of using intersection->color directly,
    // sample the texture using the UV coordinates from the intersection
    
    t_color texture_color;
    calculate_surface_properties(scene, intersection, &texture_color, &surface_normal);

    // Rest of your lighting calculations
    ambient = color_scale(&scene->ambient.color, scene->ambient.ratio);
    light_dir = vector_sub(&scene->light[0].position, &intersection->point);
    light_dir = vector_normalize(&light_dir);
    diff = fmax(0.0, vector_dot(&surface_normal, &light_dir));
    diffuse = color_scale(&scene->light[0].color, scene->light[0].bratio * diff);

    
    final_color = color_add(&ambient, &diffuse);
    // Use texture_color instead of intersection->color
    final_color = color_mul(&final_color, &texture_color);
    
    final_color.r = fmin(final_color.r, 1.0);
    final_color.g = fmin(final_color.g, 1.0);
    final_color.b = fmin(final_color.b, 1.0);
    return (colorToRgb(&final_color));
}
// int pixel_color(t_scene *scene , t_intersection *intersection, t_ray *ray)
// {
//     t_color ambient;
//     t_color diffuse;
//     t_color final_color;
//     t_vector light_dir;
//     FLOAT diff;
//     t_ray shadow_ray;

//     shadow_ray.origin = intersection->point;
//     shadow_ray.direction = vector_sub(&scene->light.position, &intersection->point);
//     shadow_ray.direction = vector_normalize(&shadow_ray.direction);
//     if (check_shadow(scene, &shadow_ray, intersection))
//         return 0x000000;
//     ambient = color_scale(&scene->ambient.color, scene->ambient.ratio);
//     light_dir = vector_sub(&scene->light.position, &intersection->point);
//     light_dir = vector_normalize(&light_dir);
//     diff = fmax(0.0, vector_dot(&intersection->normal, &light_dir));
//     diffuse = color_scale(&scene->light.color, scene->light.bratio * diff);
//     final_color = color_add(&ambient, &diffuse);
//     final_color = color_mul(&final_color, &intersection->color);
//     final_color.r = fmin(final_color.r, 1.0);
//     final_color.g = fmin(final_color.g, 1.0);
//     final_color.b = fmin(final_color.b, 1.0);
//     return (colorToRgb(&final_color));
// }
int trace_ray(t_ray *ray, t_scene *scene)
{
    t_intersection intersection;
    intersection.distance = INFINITY;
    intersection.hit = false;
    intersection.id = -1;
    intersection.hit = sphere_intersection(scene, &intersection, ray);
    intersection.hit = cylinder_intersection(scene, &intersection, ray);
    intersection.hit = plane_intersection(scene, &intersection, ray);
    // intersection.hit = cone_intersection(scene, &intersection, ray);

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
// void rotate(int *keys, t_scene *scene)
// {
//     int obj_id = my_atoi(keys, 2);
//     printf("obj_id: [%d]\n", obj_id);
//     if (obj_id == -1) 
//         return;

//     for (int i = 0; i < scene->cylinder_count; i++)
//     {
//         printf("cylinder id [%d]\n", scene->cylinder[i].id);
//         if (scene->cylinder[i].id == obj_id)
//         {
//             t_vector axis = {0, 0, 0};
//             FLOAT angle = M_PI / 4;

//             if (keys[1] == KEY_X)
//                 axis.x = 1;
//             else if (keys[1] == KEY_Y)
//                 axis.y = 1;
//             else if (keys[1] == KEY_Z)
//                 axis.z = 1;
//             rotate_point(&scene->cylinder[i].position, axis, angle);
//             rotate_point((t_point *)&scene->cylinder[i].direction, axis, angle);
//             printf("direction x[%f] y[%f] z[%f]\n", scene->cylinder[i].direction.x, scene->cylinder[i].direction.y, scene->cylinder[i].direction.z);
//             return ; 
//         }
//     }
//     for (int i = 0; i < scene->plane_count; i++)
//     {
//         if (scene->plane[i].id == obj_id)
//         {

//             t_vector axis = {0, 0, 0};
//             FLOAT angle = M_PI / 4;

//             if (keys[1] == KEY_X)
//                 axis.x = 1;
//             else if (keys[1] == KEY_Y)
//                 axis.y = 1;
//             else if (keys[1] == KEY_Z)
//                 axis.z = 1;

//             rotate_point(&scene->plane[i].position, axis, angle);
//             rotate_point((t_point *)&scene->plane[i].direction, axis, angle);
//             return ; 
//         }
//     }
// }

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
void init_textures(t_scene *scene)
{
    for (int i = 0; i < scene->plane_count; i++)
    {
            if (scene->plane[i].texture_name)
            {
                load_texture(&scene->plane[i].texture, scene->mlx, scene->plane[i].texture_name);
            }
    }
    for (int i = 0; i < scene->sphere_count; i++)
    {
            if (scene->sphere[i].texture_name)
            {
                load_texture(&scene->sphere[i].texture, scene->mlx, scene->sphere[i].texture_name);
            }
    }
    for (int i = 0; i < scene->cylinder_count; i++)
    {
            if (scene->cylinder[i].texture_name)
            {
                load_texture(&scene->cylinder[i].texture, scene->mlx, scene->cylinder[i].texture_name);
            }
    }
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
    // init_textures(scene);
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
