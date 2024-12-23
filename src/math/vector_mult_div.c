#include "./../../includes/math.h"
#include "./../../includes/base.h"

t_vector    *vec_mul(t_vector *v, FLOAT scalar)
{
    return (vec_create(v->x * scalar, v->y * scalar, v->z * scalar, NO_DEBUG));
}

t_vector    *vec_div(t_vector *v, FLOAT scalar)
{
    return (vec_create(v->x / scalar, v->y / scalar, v->z / scalar, NO_DEBUG));
}
