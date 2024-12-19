#include "./../../includes/math.h"

double      vec_dot(t_vector a, t_vector b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector    vec_cross(t_vector a, t_vector b)
{
    return (vec_create(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x));
}