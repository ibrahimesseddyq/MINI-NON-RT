#include "./../../includes/math.h"
#include "./../../includes/memory.h"
#include "./../../includes/base.h"


t_matrix    *matrix_identity(void)
{
    t_matrix *m;
    int i;
    int j;

    i = 0;
    m = arena_alloc(*get_arena(), sizeof(t_matrix));
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            m->m[i][j] = (i == j) ? 1.0 : 0.0;
            j++;
        }
        i++;
    }
    return (m);
}

t_matrix    *matrix_multiply(t_matrix *a, t_matrix *b)
{
    t_matrix *result;
    int i;
    int j;
    int k;

    i = 0;
    result = arena_alloc(*get_arena(), sizeof(t_matrix));
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            result->m[i][j] = 0;
            k = 0;
            while (k < 4)
            {
                result->m[i][j] += a->m[i][k] * b->m[k][j];
                k++;
            }
            j++;
        }
        i++;
    }
    return (result);
}

t_matrix    *matrix_translation(FLOAT x, FLOAT y, FLOAT z)
{
    t_matrix *m;

    m = matrix_identity();
    m->m[0][3] = x;
    m->m[1][3] = y;
    m->m[2][3] = z;
    return (m);
}

t_matrix    *matrix_rotation_x(FLOAT angle)
{
    t_matrix *m;
    FLOAT cos_a;
    FLOAT sin_a;

    cos_a = cos(angle);
    sin_a = sin(angle);
    m = matrix_identity();
    m->m[1][1] = cos_a;
    m->m[1][2] = -sin_a;
    m->m[2][1] = sin_a;
    m->m[2][2] = cos_a;
    return (m);
}

t_matrix    *matrix_rotation_y(FLOAT angle)
{
    t_matrix *m;
    FLOAT cos_a;
    FLOAT sin_a;

    cos_a = cos(angle);
    sin_a = sin(angle);
    m = matrix_identity();
    m->m[0][0] = cos_a;
    m->m[0][2] = sin_a;
    m->m[2][0] = -sin_a;
    m->m[2][2] = cos_a;
    return (m);
}

t_matrix    *matrix_rotation_z(FLOAT angle)
{
    t_matrix *m;
    FLOAT cos_a;
    FLOAT sin_a;

    cos_a = cos(angle);
    sin_a = sin(angle);
    m = matrix_identity();
    m->m[0][0] = cos_a;
    m->m[0][1] = -sin_a;
    m->m[1][0] = sin_a;
    m->m[1][1] = cos_a;
    return (m);
}

t_matrix    *matrix_scaling(FLOAT x, FLOAT y, FLOAT z)
{
    t_matrix *m;

    m = matrix_identity();
    m->m[0][0] = x;
    m->m[1][1] = y;
    m->m[2][2] = z;
    return (m);
}

t_vector    *matrix_multiply_vector(t_matrix *m, t_vector *v)
{
    t_vector *result;
    FLOAT w;

    result = vec_create(0, 0, 0, NO_DEBUG);
    result->x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z + m->m[0][3];
    result->y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z + m->m[1][3];
    result->z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z + m->m[2][3];
    w = m->m[3][0] * v->x + m->m[3][1] * v->y + m->m[3][2] * v->z + m->m[3][3];

    if (w != 1.0 && w != 0.0)
    {
        result->x /= w;
        result->y /= w;
        result->z /= w;
    }
    return (result);
}