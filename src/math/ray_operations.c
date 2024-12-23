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
t_intersection *ray_cylinder_intersect(t_ray *ray, t_vector *center, FLOAT diameter, FLOAT height)
{
    // t_intersection *result = arena_alloc(*get_arena(), sizeof(t_intersection));
    t_intersection *result = malloc(sizeof(t_intersection));

    result->hit = false;
    
    FLOAT radius = diameter / 2.0;
    const FLOAT EPSILON = 1e-8;

    // Calculate cylinder axis (assuming it's aligned with Y-axis)
    t_vector *cylinder_axis = vec_create(0, 1, 0, NO_DEBUG);
    
    // Calculate vector from ray origin to cylinder center
    t_vector *oc = vec_sub(ray->origin, center);
    
    // Calculate components for quadratic equation
    t_vector *cross_dir_axis = vec_cross(ray->direction, cylinder_axis);
    t_vector *cross_oc_axis = vec_cross(oc, cylinder_axis);
    
    FLOAT a = vec_dot(cross_dir_axis, cross_dir_axis);
    FLOAT b = 2.0 * vec_dot(cross_dir_axis, cross_oc_axis);
    FLOAT c = vec_dot(cross_oc_axis, cross_oc_axis) - (radius * radius);
    
    // Solve quadratic equation
    FLOAT discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return result;
        
    FLOAT t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    FLOAT t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    
    // Sort intersections
    if (t1 > t2)
    {
        FLOAT temp = t1;
        t1 = t2;
        t2 = temp;
    }
    
    // Check intersection points against cylinder height
    FLOAT y1 = ray->origin->y + t1 * ray->direction->y;
    FLOAT y2 = ray->origin->y + t2 * ray->direction->y;
    
    // Adjust intersection points based on cylinder height
    if (y1 < center->y || y1 > center->y + height)
        t1 = t2;
    if (y2 < center->y || y2 > center->y + height)
        t2 = t1;
        
    FLOAT t = (t1 < t2) ? t1 : t2;
    
    if (t > EPSILON)
    {
        result->hit = true;
        result->distance = t;
        result->point = vec_add(ray->origin, vec_mul(ray->direction, t));
        
        // Calculate normal at intersection point
        t_vector *pc = vec_sub(result->point, center);
        FLOAT y = vec_dot(pc, cylinder_axis);
        t_vector *proj = vec_mul(cylinder_axis, y);
        result->normal = vec_normalize(vec_sub(pc, proj));
        
        // Check if we need to cap the cylinder
        if (result->point->y <= center->y || result->point->y >= center->y + height)
        {
            // Use plane intersection for caps
            t_vector *cap_center = vec_add(center, 
                vec_mul(cylinder_axis, (result->point->y <= center->y) ? 0 : height));
            t_intersection *cap_hit = ray_plane_intersect(ray, cap_center, cylinder_axis);
            
            if (cap_hit->hit)
            {
                t_vector *p = cap_hit->point;
                FLOAT dist_to_center = sqrt(
                    pow(p->x - center->x, 2) + 
                    pow(p->z - center->z, 2)
                );
                
                if (dist_to_center <= radius)
                {
                    result->point = cap_hit->point;
                    result->normal = cap_hit->normal;
                    result->distance = cap_hit->distance;
                }
            }
        }
    }
    
    return result;
}
t_intersection *ray_sphere_intersect(t_ray *ray, t_vector *center, FLOAT diameter)
{
    // t_intersection *result = arena_alloc(*get_arena(), sizeof(t_intersection));
    t_intersection *result = malloc(sizeof(t_intersection));

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

    // result = arena_alloc(*get_arena(), sizeof(t_intersection));
    result = malloc(sizeof(t_intersection));

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