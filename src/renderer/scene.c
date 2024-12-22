#include "../../includes/objects.h"
#include "../../includes/map.h"
#include "../../includes/memory.h"
#include "./../../minirt.h"
// TODO Soufiane
void create_scene(t_scene *scene)
{

}

t_color *trace_ray(t_ray *ray, t_scene *scene)
{
    t_intersection    *closest_hit;
    t_color          *hit_color;
    FLOAT            min_distance;
    int              i;

    min_distance = INFINITY;
    closest_hit->hit = false;
    hit_color = arena_alloc(*get_arena(), sizeof(t_color));
    if (!hit_color)
        return (NULL);
    
    // Set background color (black)
    hit_color->r = 0;
    hit_color->g = 0;
    hit_color->b = 0;

    // Check all spheres
    i = 0;
    while (i < scene->sphere_count)
    {
        t_intersection *hit = ray_sphere_intersect(ray, &scene->sphere[i].position, 
                                                scene->sphere[i].diameter);
        if (hit->hit && hit->distance < min_distance)
        {
            min_distance = hit->distance;
            closest_hit = hit;
            hit_color->r = scene->sphere[i].r;
            hit_color->g = scene->sphere[i].g;
            hit_color->b = scene->sphere[i].b;
        }
        i++;
    }

    // Check all planes
    i = 0;
    while (i < scene->plane_count)
    {
        t_vector *normal = vec_create(scene->plane[i].vx,
                                   scene->plane[i].vy,
                                   scene->plane[i].vz);
        t_intersection *hit = ray_plane_intersect(ray, &scene->plane[i].position, normal);
        if (hit->hit && hit->distance < min_distance)
        {
            min_distance = hit->distance;
            closest_hit = hit;
            hit_color->r = scene->plane[i].r;
            hit_color->g = scene->plane[i].g;
            hit_color->b = scene->plane[i].b;
        }
        i++;
    }

    // Check all cylinders
    // i = 0;
    // while (i < scene->cylinder_count)
    // {
    //     t_intersection *hit = ray_cylinder_intersect(ray, &scene->cylinder[i]);
    //     if (hit->hit && hit->distance < min_distance)
    //     {
    //         min_distance = hit->distance;
    //         closest_hit = hit;
    //         hit_color->r = scene->cylinder[i].r;
    //         hit_color->g = scene->cylinder[i].g;
    //         hit_color->b = scene->cylinder[i].b;
    //     }
    //     i++;
    // }

    return (hit_color);
}
t_map *render_scene(t_scene *scene)
{
    int x;
    int y;
    FLOAT pixel_x;
    FLOAT pixel_y;
    t_vector *direction;
    t_ray *ray;
    t_color *pixel_color;
    t_map *map;

    map = arena_alloc(*get_arena(), sizeof(t_map));
    map->points = arena_alloc(*get_arena(), sizeof(t_color *) * scene->width);
    for (int i = 0; i < scene->width; i++)
    {
        map->points[i] = arena_alloc(*get_arena(), sizeof(t_color) * scene->height);
    }

    y = 0;
    while (y < scene->height)
    {
        x = 0;
        while (x < scene->width)
        {
            pixel_x = (2.0 * x / scene->width - 1.0);
            pixel_y = (1.0 - 2.0 * y / scene->height);
            direction = vec_normalize(vec_create(pixel_x, pixel_y, scene->viewport_dist));
           
            ray = ray_create(&scene->camera.position, direction);
            pixel_color = trace_ray(ray, scene);

            map->points[x][y] = *pixel_color;
            x++;
        }
        y++;
    }

    return (map);
}
void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

// Render the map to MLX window
void render_to_window(t_data *data)
{
    int x;
    int y;
    t_color color;
    int mlx_color;

    y = 0;
    while (y < data->scene->height)
    {
        x = 0;
        while (x < data->scene->width)
        {
            color = data->map->points[x][y];
            mlx_color = create_rgb(color.r, color.g, color.b);
            my_mlx_pixel_put(&data->mlx->img, x, y, mlx_color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img.img, 0, 0);
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == 53)  // ESC key
    {
        mlx_destroy_window(data->mlx->mlx, data->mlx->win);
        // Memory cleanup handled by arena
        exit(0);
    }
    return (0);
}

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx->mlx, data->mlx->win);
    // Memory cleanup handled by arena
    exit(0);
    return (0);
}

t_mlx *init_mlx(t_scene *scene)
{
    t_mlx *mlx;

    // mlx = arena_alloc(*get_arena(), sizeof(t_mlx));
    mlx->mlx = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx, scene->width, scene->height, "MiniRT");
    mlx->img.img = mlx_new_image(mlx->mlx, scene->width, scene->height);
    mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
                                     &mlx->img.line_length, &mlx->img.endian);
    return (mlx);
}

void render(t_scene *scene)
{
    t_data data;

    data.scene = scene;
    data.mlx->mlx = mlx_init();
    data.mlx->win = mlx_new_window(data.mlx->mlx, WIDTH , HEIGHT, "MiniRT");
    data.mlx->img.img = mlx_new_image(data.mlx->mlx, WIDTH, HEIGHT);
    data.mlx->img.addr = mlx_get_data_addr(data.mlx->img.img, &data.mlx->img.bits_per_pixel,
                                     &data.mlx->img.line_length, &data.mlx->img.endian);

    mlx_put_image_to_window(data.mlx->mlx, data.mlx->win, data.mlx->img.img, 0, 0);
    // data.map = render_scene(scene);
    mlx_loop(data.mlx->mlx);

}
