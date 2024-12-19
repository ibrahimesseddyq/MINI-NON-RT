#include "./../../includes/math.h"

t_vector    vec_create(double x, double y, double z)
{
    t_vector v;
    
    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

double      vec_length(t_vector v)
{
    return (sqrt(vec_dot(v, v)));
}

t_vector    vec_normalize(t_vector v)
{
    double length;

    length = vec_length(v);
    if (length > 0)
        return (vec_div(v, length));
    return (v);
}

t_vector    vec_rotate(t_vector v, t_vector axis, double angle)
{
    t_vector result;
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    t_vector normalized_axis = vec_normalize(axis);
    double dot_product = vec_dot(v, normalized_axis);

    result.x = v.x * cos_angle + 
        (normalized_axis.y * v.z - normalized_axis.z * v.y) * sin_angle + 
        normalized_axis.x * dot_product * (1 - cos_angle);

    result.y = v.y * cos_angle + 
        (normalized_axis.z * v.x - normalized_axis.x * v.z) * sin_angle + 
        normalized_axis.y * dot_product * (1 - cos_angle);

    result.z = v.z * cos_angle + 
        (normalized_axis.x * v.y - normalized_axis.y * v.x) * sin_angle + 
        normalized_axis.z * dot_product * (1 - cos_angle);

    return (result);
}
