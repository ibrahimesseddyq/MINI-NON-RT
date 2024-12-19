#include "./../../includes/math.h"

t_vector    vec_mul(t_vector v, double scalar)
{
    return (vec_create(v.x * scalar, v.y * scalar, v.z * scalar));
}

t_vector    vec_div(t_vector v, double scalar)
{
    return (vec_create(v.x / scalar, v.y / scalar, v.z / scalar));
}
