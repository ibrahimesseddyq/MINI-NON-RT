#include "./../../includes/math.h"
#include "./../../includes/memory.h"

t_ray       *ray_create(t_vector *origin, t_vector *direction)
{
    t_ray *ray;

    ray = arena_alloc(*get_arena(), sizeof(t_ray));
    ray->origin = origin;
    ray->direction = direction;
    return (ray);
}

// t_intersection *ray_sphere_intersect(t_ray *ray, t_vector *center, FLOAT diameter)
// {
//     t_intersection *result;
//     t_vector *oc;
//     // FLOAT a;
//     // FLOAT b;
//     // FLOAT c;
//     // FLOAT discriminant;
//     FLOAT radius = diameter / 2.0;  // Make sure you're using radius, not diameter
//     FLOAT t;
//     result = arena_alloc(*get_arena(), sizeof(t_intersection));


//     oc = vec_sub(ray->origin, center);

//     FLOAT a = vec_dot(ray->direction, ray->direction);
//     FLOAT b = 2.0 * vec_dot(oc, ray->direction);
//     FLOAT c = vec_dot(oc, oc) - (radius * radius);


//     FLOAT discriminant = b * b - 4 * a * c;

//     if (discriminant >= 0)
//     {
//         t = (-b - sqrt(discriminant)) / (2.0f * a);
//         if (t > 0)
//         {
//             result->hit = true;
//             result->distance = t;
//             result->point = vec_add(ray->origin, vec_mul(ray->direction, t));
//             result->normal = vec_normalize(vec_sub(result->point, center));
//         }
//     }
//     return (result);
// }

t_intersection *ray_sphere_intersect(t_ray *ray, t_vector *center, FLOAT diameter)
{
    t_intersection *result = arena_alloc(*get_arena(), sizeof(t_intersection));
    result->hit = false;

    FLOAT radius = diameter / 2.0;  
    const FLOAT EPSILON = 1e-8;

    // Detailed vector calculations
    t_vector *oc = vec_sub(ray->origin, center);

    // Print detailed vector information
    printf("Detailed Vector Intersection Check:\n");
    printf("  Ray Origin       : [%f, %f, %f]\n", ray->origin->x, ray->origin->y, ray->origin->z);
    printf("  Sphere Center    : [%f, %f, %f]\n", center->x, center->y, center->z);
    printf("  OC Vector        : [%f, %f, %f]\n", oc->x, oc->y, oc->z);
    printf("  Ray Direction    : [%f, %f, %f]\n", ray->direction->x, ray->direction->y, ray->direction->z);
    
    // Distance calculations
    FLOAT a = vec_dot(ray->direction, ray->direction);
    FLOAT b = 2.0 * vec_dot(oc, ray->direction);
    FLOAT c = vec_dot(oc, oc) - (radius * radius);

    printf("  Quadratic Coefficients:\n");
    printf("    a: %f\n", a);
    printf("    b: %f\n", b);
    printf("    c: %f\n", c);

    // Calculate discriminant
    FLOAT discriminant = b * b - 4 * a * c;
    printf("  Discriminant     : %f\n", discriminant);

    // Calculate distance to sphere surface
    FLOAT sphere_distance = vec_length(oc) - radius;
    printf("  Distance to Sphere Surface: %f\n", sphere_distance);

    // More detailed intersection logic
    if (discriminant >= 0)
    {
        FLOAT sqrtDiscriminant = sqrt(discriminant);
        FLOAT t1 = (-b - sqrtDiscriminant) / (2.0f * a);
        FLOAT t2 = (-b + sqrtDiscriminant) / (2.0f * a);

        printf("  Intersection Distances:\n");
        printf("    t1: %f\n", t1);
        printf("    t2: %f\n", t2);

        // Choose the closer positive intersection
        FLOAT t = (t1 > 0) ? t1 : t2;

        if (t > 0)
        {
            result->hit = true;
            result->distance = t;
            result->point = vec_add(ray->origin, vec_mul(ray->direction, t));
            result->normal = vec_normalize(vec_sub(result->point, center));

            printf("  Hit Point         : [%f, %f, %f]\n", 
                   result->point->x, result->point->y, result->point->z);
        }
    }

    return result;
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