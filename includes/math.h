#ifndef MATH_H
#define MATH_H
#include <math.h>
#include <stdbool.h>
#define PI 3.14159265358979323846

typedef struct
{
    double x;
    double y;
    double z;
} t_vector;

typedef struct
{
    double r;
    double g;
    double b;
} t_color;

typedef struct
{
    double m[4][4];
} t_matrix;

typedef struct
{
    bool hit;
    double distance;
    t_vector point;
    t_vector normal;
} t_intersection;

typedef struct
{
    t_vector origin;
    t_vector direction;
} t_ray;

// Vector Operations
t_vector    vec_create(double x, double y, double z);
t_vector    vec_add(t_vector a, t_vector b);
t_vector    vec_sub(t_vector a, t_vector b);
t_vector    vec_mul(t_vector v, double scalar);
t_vector    vec_div(t_vector v, double scalar);
double      vec_dot(t_vector a, t_vector b);
t_vector    vec_cross(t_vector a, t_vector b);
double      vec_length(t_vector v);
t_vector    vec_normalize(t_vector v);
t_vector    vec_rotate(t_vector v, t_vector axis, double angle);

// Color Operations
t_color     color_create(double r, double g, double b);
t_color     color_add(t_color a, t_color b);
t_color     color_mul(t_color c, double scalar);
t_color     color_multiply(t_color a, t_color b);
t_color     color_clamp(t_color c);

// Math Utilities
double      deg_to_rad(double degrees);
double      rad_to_deg(double radians);

// Matrix Operations
t_matrix    matrix_identity(void);
t_matrix    matrix_multiply(t_matrix a, t_matrix b);
t_matrix    matrix_translation(double x, double y, double z);
t_matrix    matrix_rotation_x(double angle);
t_matrix    matrix_rotation_y(double angle);
t_matrix    matrix_rotation_z(double angle);
t_matrix    matrix_scaling(double x, double y, double z);
t_vector    matrix_multiply_vector(t_matrix m, t_vector v);

// Ray Operations
t_ray       ray_create(t_vector origin, t_vector direction);
t_intersection ray_sphere_intersect(t_ray ray, t_vector center, double radius);
t_intersection ray_plane_intersect(t_ray ray, t_vector point, t_vector normal);
#endif