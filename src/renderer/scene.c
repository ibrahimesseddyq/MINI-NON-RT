#include "../../includes/objects.h"
#include "../../includes/map.h"
#include "../../includes/memory.h"
#include "./../../minirt.h"
void print_ambient(const t_ambient *ambient) {
    printf("Ambient Light:\n");
    printf("  Ratio: %f\n", ambient->ratio);
    printf("  RGB: (%d, %d, %d)\n", ambient->r, ambient->g, ambient->b);
}

// Printer for t_camera
void print_camera(const t_camera *camera) {
    printf("Camera:\n");
    printf("  Position: (%.2f, %.2f, %.2f)\n", 
           camera->position.x, camera->position.y, camera->position.z);
    printf("  Direction: (%.2f, %.2f, %.2f)\n", 
           camera->direction.x, camera->direction.y, camera->direction.z);
    printf("  FOV: %d\n", camera->fov);
}

// Printer for t_light
void print_light(const t_light *light) {
    printf("Light:\n");
    printf("  Position: (%.2f, %.2f, %.2f)\n", 
           light->position.x, light->position.y, light->position.z);
    printf("  Brightness Ratio: %f\n", light->bratio);
    printf("  RGB: (%d, %d, %d)\n", light->r, light->g, light->b);
}

// Printer for t_sphere
void print_sphere(const t_sphere *sphere) {
    printf("Sphere:\n");
    printf("  Position: (%.2f, %.2f, %.2f)\n", 
           sphere->position.x, sphere->position.y, sphere->position.z);
    printf("  Diameter: %f\n", sphere->diameter);
    printf("  RGB: (%d, %d, %d)\n", sphere->r, sphere->g, sphere->b);
}

// Printer for t_plane
void print_plane(const t_plane *plane) {
    printf("Plane:\n");
    printf("  Position: (%.2f, %.2f, %.2f)\n", 
           plane->position.x, plane->position.y, plane->position.z);
    printf("  Normal Vector: (%.2f, %.2f, %.2f)\n", 
           plane->vx, plane->vy, plane->vz);
    printf("  RGB: (%d, %d, %d)\n", plane->r, plane->g, plane->b);
}

// Printer for t_cylinder
void print_cylinder(const t_cylinder *cylinder) {
    printf("Cylinder:\n");
    printf("  Position: (%.2f, %.2f, %.2f)\n", 
           cylinder->position.x, cylinder->position.y, cylinder->position.z);
    printf("  Axis Vector: (%.2f, %.2f, %.2f)\n", 
           cylinder->vx, cylinder->vy, cylinder->vz);
    printf("  Diameter: %f\n", cylinder->diameter);
    printf("  Height: %f\n", cylinder->height);
    printf("  RGB: (%d, %d, %d)\n", cylinder->r, cylinder->g, cylinder->b);
}

// Printer for t_vector
void print_vector(const t_vector *vector) {
    printf("Vector/Point:\n");
    printf("  Coordinates: (%.2f, %.2f, %.2f)\n", 
           vector->x, vector->y, vector->z);
    printf("  Is Vector: %s\n", vector->is_vec ? "Yes" : "No");
}

// Printer for t_scene (overview)
void print_scene(const t_scene *scene) {
    printf("Scene Details:\n");
    printf("  Viewport Width: %f\n", scene->viewport_width);
    printf("  Viewport Height: %f\n", scene->viewport_height);
    printf("  Scene Width: %f\n", scene->width);
    printf("  Scene Height: %f\n", scene->height);
    printf("  Viewport Distance: %f\n", scene->viewport_dist);
    
    printf("\n--- Camera ---\n");
    print_camera(&scene->camera);
    
    printf("\n--- Light ---\n");
    print_light(&scene->light);
    
    printf("\n--- Ambient Light ---\n");
    print_ambient(&scene->ambient);
    
    printf("\n--- Object Counts ---\n");
    printf("  Planes: %d\n", scene->plane_count);
    printf("  Cylinders: %d\n", scene->cylinder_count);
    printf("  Spheres: %d\n", scene->sphere_count);
}
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

    closest_hit = arena_alloc(*get_arena(), sizeof(t_intersection));

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
        // printf("sphere count [%d] sphere diameter [%f]\n", scene->sphere_count, scene->sphere[i].diameter);
        // printf("ray origin [%f][%f][%f] ray direction [%f][%f][%f] sphere pos [%f][%f][%f] sphere diameter [%d][%f]\n", ray->origin->x, ray->origin->y, ray->origin->z, ray->direction->x, ray->direction->y, ray->direction->z, i, scene->sphere[i].diameter);
        // if (hit->hit)
        // {
        //     printf("did SPHERE HIT\n");
        // }
        // else
        //     printf("not SPHERE HIT\n");
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
    // i = 0;
    // while (i < scene->plane_count)
    // {
    //     t_vector *normal = vec_create(scene->plane[i].vx,
    //                                scene->plane[i].vy,
    //                                scene->plane[i].vz, NO_DEBUG);
    //     t_intersection *hit = ray_plane_intersect(ray, &scene->plane[i].position, normal);
    //     if (hit->hit && hit->distance < min_distance)
    //     {
    //         min_distance = hit->distance;
    //         closest_hit = hit;
    //         hit_color->r = scene->plane[i].r;
    //         hit_color->g = scene->plane[i].g;
    //         hit_color->b = scene->plane[i].b;
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

    x = 0;
    y = 0;
    print_scene(scene);
    map = arena_alloc(*get_arena(), sizeof(t_map));
    map->points = arena_alloc(*get_arena(), sizeof(t_color *) * WIDTH);
    for (int i = 0; i < WIDTH; i++)
        map->points[i] = arena_alloc(*get_arena(), sizeof(t_color) * HEIGHT);

    FLOAT fov_scale = tan((scene->camera.fov * PI) / 360.0);
    FLOAT aspect = (FLOAT)WIDTH / HEIGHT;


    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            // Calculate and print pixel_x at each step
            pixel_x = (2.0 * ((FLOAT)x / WIDTH) - 1.0) * aspect * fov_scale;
            // printf("Step 1 - x=%d, pixel_x=%f\n", x, pixel_x);

            pixel_y = (1.0 - 2.0 * ((FLOAT)y / HEIGHT)) * fov_scale;
            
            // Create and print direction before normalization
            direction = vec_create(pixel_x, pixel_y, 1.0, DEBUG_RENDER_SCENE_VECTOR_CREATE);
            // printf("Step 2 - After vec_create: x=%f\n", direction->x);

            // Print before normalization
            // printf("Step 3 - Before normalize: x=%f, y=%f, z=%f\n", 
            //        direction->x, direction->y, direction->z);
            
            direction = vec_normalize(direction);
            
            // // Print after normalization
            // printf("Step 4 - After normalize: x=%f, y=%f, z=%f\n", 
            //        direction->x, direction->y, direction->z);

            ray = ray_create(&scene->camera.position, direction);

            // // Print final ray direction
            // printf("Step 5 - Final ray direction: x=%f, y=%f, z=%f\n\n", 
            //        ray->direction->x, ray->direction->y, ray->direction->z);

            pixel_color = trace_ray(ray, scene);
            map->points[x][y] = *pixel_color;
            x++;
        }
        y++;
        // printf("height is [%d]\n", y);
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
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
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

    mlx = arena_alloc(*get_arena(), sizeof(t_mlx));
    mlx->mlx = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "MiniRT");
    mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
                                     &mlx->img.line_length, &mlx->img.endian);
    return (mlx);
}

void render(t_scene *scene)
{
    t_data data;
    t_mlx *mlx;
    mlx = init_mlx(scene);
    data.map = render_scene(scene);
    data.scene = scene;
    data.mlx = mlx;
    render_to_window(&data);
    mlx_key_hook(mlx->win, key_hook, &data);
    mlx_hook(mlx->win, 17, 0, close_window, &data); 
    mlx_loop(mlx->mlx);
}
