#ifndef MATH_H
#define MATH_H
#include "base.h"
#include <math.h>
#include <stdbool.h>
#define PI 3.14159265358979323846

typedef struct s_vector
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
    int is_vec;
} t_vector;

typedef t_vector t_point;
typedef struct s_color
{
    FLOAT r;
    FLOAT g;
    FLOAT b;
} t_color;

typedef struct
{
    FLOAT m[4][4];
} t_matrix;

typedef struct s_intersection
{
    bool hit;
    FLOAT distance;
    t_vector *point;
    t_vector *normal;
} t_intersection;

typedef struct s_ray
{
    t_vector *origin;
    t_vector *direction;
} t_ray;

// Vector Operations
t_vector    *vec_create(FLOAT x, FLOAT y, FLOAT z, int debug_flag);
t_vector    *vec_add(t_vector *a, t_vector *b);
t_vector    *vec_sub(t_vector *a, t_vector *b);
t_vector    *vec_mul(t_vector *v, FLOAT scalar);
t_vector    *vec_div(t_vector *v, FLOAT scalar);
FLOAT      vec_dot(t_vector *a, t_vector *b);
t_vector    *vec_cross(t_vector *a, t_vector *b);
FLOAT      vec_length(t_vector *v);
t_vector    *vec_normalize(t_vector *v);
t_vector    *vec_rotate(t_vector *v, t_vector *axis, FLOAT angle);
// Point Operations
t_point *create_point(FLOAT x, FLOAT y, FLOAT z);
// Color Operations
t_color     *color_create(FLOAT r, FLOAT g, FLOAT b);
t_color     *color_add(t_color *a, t_color *b);
t_color     *color_mul(t_color *c, FLOAT scalar);
t_color     *color_multiply(t_color *a, t_color *b);
t_color     *color_clamp(t_color *c);

// Math Utilities
FLOAT      deg_to_rad(FLOAT degrees);
FLOAT      rad_to_deg(FLOAT radians);

// Matrix Operations
t_matrix    *matrix_identity(void);
t_matrix    *matrix_multiply(t_matrix *a, t_matrix *b);
t_matrix    *matrix_translation(FLOAT x, FLOAT y, FLOAT z);
t_matrix    *matrix_rotation_x(FLOAT angle);
t_matrix    *matrix_rotation_y(FLOAT angle);
t_matrix    *matrix_rotation_z(FLOAT angle);
t_matrix    *matrix_scaling(FLOAT x, FLOAT y, FLOAT z);
t_vector    *matrix_multiply_vector(t_matrix *m, t_vector *v);

// Ray Operations
t_ray       *ray_create(t_vector *origin, t_vector *direction);
t_intersection *ray_sphere_intersect(t_ray *ray, t_vector *center, FLOAT radius);
t_intersection *ray_plane_intersect(t_ray *ray, t_vector *point, t_vector *normal);
t_intersection *ray_cylinder_intersect(t_ray *ray, t_vector *center, FLOAT diameter, FLOAT height);

t_vector *computeReflectionRay(t_vector *incident, t_vector *normal);
t_vector *computeRefractionRay(t_vector *incident, t_vector *normal, FLOAT n1, FLOAT n2);
void computeFresnel(FLOAT n1, FLOAT n2, FLOAT cos_i, FLOAT *Kr, FLOAT *Kt);
#endif