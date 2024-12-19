#include "./../../includes/math.h"

t_vector    vec_add(t_vector a, t_vector b)
{
    return (vec_create(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vector    vec_sub(t_vector a, t_vector b)
{
    return (vec_create(a.x - b.x, a.y - b.y, a.z - b.z));
}