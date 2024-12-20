#include "./../../includes/math.h"
#include "./../../includes/memory.h"

t_vector    *vec_create(FLOAT x, FLOAT y, FLOAT z)
{
    t_vector *v;
    
    v = arena_alloc(*get_arena(), sizeof(t_vector));
    v->x = x;
    v->y = y;
    v->z = z;
    v->is_vec = 1;
    return (v);
}

FLOAT      vec_length(t_vector *v)
{
    return (sqrt(vec_dot(v, v)));
}

t_vector    *vec_normalize(t_vector *v)
{
    FLOAT length;

    length = vec_length(v);
    if (length > 0)
        return (vec_div(v, length));
    return (v);
}

t_vector    *vec_rotate(t_vector *v, t_vector *axis, FLOAT angle)
{
    t_vector *result;
    FLOAT cos_angle = cos(angle);
    FLOAT sin_angle = sin(angle);
    t_vector *normalized_axis;
    
    normalized_axis = vec_normalize(axis);
    FLOAT dot_product = vec_dot(v, normalized_axis);

    result->x = v->x * cos_angle + 
        (normalized_axis->y * v->z - normalized_axis->z * v->y) * sin_angle + 
        normalized_axis->x * dot_product * (1 - cos_angle);

    result->y = v->y * cos_angle + 
        (normalized_axis->z * v->x - normalized_axis->x * v->z) * sin_angle + 
        normalized_axis->y * dot_product * (1 - cos_angle);

    result->z = v->z * cos_angle + 
        (normalized_axis->x * v->y - normalized_axis->y * v->x) * sin_angle + 
        normalized_axis->z * dot_product * (1 - cos_angle);

    return (result);
}
