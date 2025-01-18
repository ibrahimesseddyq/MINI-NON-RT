#include "./../../../minirt.h"

t_vector point_to_vector(t_point *point)
{
    t_vector vector;
    vector.x = point->x;
    vector.y = point->y;
    vector.z = point->z;
    return (vector);
}
FLOAT hit_cone(t_point *vertex, t_vector *axis, double angle, t_ray *ray)
{
    t_vector oc = vector_sub(&ray->origin, vertex);
    double cos2 = cos(angle) * cos(angle);
    double sin2 = sin(angle) * sin(angle);

    FLOAT a = vector_dot(&ray->direction, axis) * vector_dot(&ray->direction, axis) - cos2;
    FLOAT b = 2.0 * (vector_dot(&ray->direction, axis) * vector_dot(&oc, axis) - vector_dot(&ray->direction, &oc) * cos2);
    FLOAT c = vector_dot(&oc, axis) * vector_dot(&oc, axis) - vector_dot(&oc, &oc) * cos2;

    FLOAT discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return -1;

    FLOAT t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    FLOAT t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    FLOAT t;
    if (t1 > 0 && t2 > 0)
        t = fmin(t1, t2);
    else if (t1 > 0)
        t = t1;
    else if (t2 > 0)
        t = t2;
    else
        return -1;

    // Verify intersection point lies within the cone's finite height
    t_vector scaled_v = vector_scale(&ray->direction, t);
    t_vector hit_point = vector_add(&ray->origin, &scaled_v);
    t_vector cone_to_hit = vector_sub(&hit_point, vertex);
    if (vector_dot(&cone_to_hit, axis) < 0 || vector_dot(&cone_to_hit, axis) > vector_length(axis))
        return -1;

    return t;
}


bool cone_intersection(t_scene *scene, t_intersection *intersection, t_ray *ray)
{
    int i;
    FLOAT t;
    t_vector tmp;

    i = scene->cone_count;
    while (i--)
    {
        t = hit_cone(&scene->cone[i].vertex, &scene->cone[i].axis, scene->cone[i].angle, ray);
        if (t > 0 && t < intersection->distance)
        {
            intersection->hit = true;
            intersection->id = scene->cone[i].id;
            intersection->distance = t;

            // Update intersection point, normal, and color
            intersection->color = scene->cone[i].color;
            tmp = vector_scale(&ray->direction, t);
            intersection->point = vector_add(&ray->origin, &tmp);

            t_vector cone_to_point = vector_sub(&intersection->point, &scene->cone[i].vertex);
            t_vector axis_scaled = vector_scale(&scene->cone[i].axis, vector_dot(&cone_to_point, &scene->cone[i].axis));
            t_vector subs_vec = vector_sub(&cone_to_point, &axis_scaled);
            intersection->normal = vector_normalize(&subs_vec);
        }
    }
    return (intersection->hit);
}
