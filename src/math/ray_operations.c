#include "./../../includes/math.h"
#include "./../../includes/memory.h"

t_ray       *ray_create(t_vector *origin, t_vector *direction)
{
    t_ray *ray;

    ray = arena_alloc(*get_arena(), sizeof(t_ray));
    ray->origin = origin;
    ray->direction = vec_normalize(direction);
    return (ray);
}

t_intersection *ray_sphere_intersect(t_ray *ray, t_vector *center, FLOAT radius)
{
    t_intersection *result;
    t_vector *oc;
    FLOAT a;
    FLOAT b;
    FLOAT c;
    FLOAT discriminant;
    FLOAT t;

    result = arena_alloc(*get_arena(), sizeof(t_intersection));
    oc = arena_alloc(*get_arena(), sizeof(t_vector));
    oc = vec_sub(ray->origin, center);
    a = vec_dot(ray->direction, ray->direction);
    b = 2.0 * vec_dot(oc, ray->direction);
    c = vec_dot(oc, oc) - radius * radius;
    discriminant = b * b - 4 * a * c;

    result->hit = false;
    if (discriminant >= 0)
    {
        t = (-b - sqrt(discriminant)) / (2.0 * a);
        if (t > 0)
        {
            result->hit = true;
            result->distance = t;
            result->point = vec_add(ray->origin, vec_mul(ray->direction, t));
            result->normal = vec_normalize(vec_sub(result->point, center));
        }
    }
    return (result);
}

t_intersection *ray_plane_intersect(t_ray *ray, t_vector *point, t_vector *normal)
{
    t_intersection *result;
    FLOAT denom;
    FLOAT t;

    result = arena_alloc(*get_arena(), sizeof(t_intersection));
    denom = vec_dot(normal, ray->direction);
    result->hit = false;

    if (fabs(denom) > 0.0001)
    {
        t = vec_dot(vec_sub(point, ray->origin), normal) / denom;
        if (t > 0)
        {
            result->hit = true;
            result->distance = t;
            result->point = vec_add(ray->origin, vec_mul(ray->direction, t));
            result->normal = normal;
            if (denom > 0)
                result->normal = vec_mul(normal, -1);
        }
    }
    return (result);
}