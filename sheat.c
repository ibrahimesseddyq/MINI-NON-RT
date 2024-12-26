#include <math.h>
#include "vector.h"
#include "color.h"
#include "ray.h"
#include "scene.h"

#define AMBIENT_STRENGTH 0.2
#define LIGHT_INTENSITY 0.7

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

        // Ambient lighting
        int ambient_color = color(255, 255, 255); // White light
        t_color ambient = color_scale(&ambient_color, AMBIENT_STRENGTH);

        // Diffuse lighting
        t_vector light_dir = vector_sub(&scene->light.position, &intersection.point);
        light_dir = vector_normalize(&light_dir);
        FLOAT diff = fmax(0.0, vector_dot(&light_dir, &intersection.normal));
        int light_color = color(255, 255, 255); // White light
        t_color diffuse = color_scale(&light_color, LIGHT_INTENSITY * diff);

        // Combine ambient and diffuse lighting
        t_color final_color = color_add(&ambient, &diffuse);

        return color_to_int(&final_color);
    }
    return 0x000000;
}