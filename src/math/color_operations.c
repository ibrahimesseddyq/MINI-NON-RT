#include "./../../includes/math.h"
#include "./../../includes/memory.h"

t_color     *color_create(FLOAT r, FLOAT g, FLOAT b)
{
    t_color *c;

    c = arena_alloc(*get_arena(), sizeof(t_color));
    c->r = r;
    c->g = g;
    c->b = b;
    return (c);
}

t_color     *color_clamp(t_color *c)
{
    t_color *result;

    result = arena_alloc(*get_arena(), sizeof(t_color));
    result->r = fmin(fmax(c->r, 0.0), 1.0);
    result->g = fmin(fmax(c->g, 0.0), 1.0);
    result->b = fmin(fmax(c->b, 0.0), 1.0);
    return (result);
}


t_color     *color_add(t_color *a, t_color *b)
{
    t_color *result;

    result = arena_alloc(*get_arena(), sizeof(t_color));
    result->r = a->r + b->r;
    result->g = a->g + b->g;
    result->b = a->b + b->b;
    return (result);
}

t_color     *color_mul(t_color *c, FLOAT scalar)
{
    t_color *result;

    result = arena_alloc(*get_arena(), sizeof(t_color));
    result->r = c->r * scalar;
    result->g = c->g * scalar;
    result->b = c->b * scalar;
    return (result);
}

t_color     *color_multiply(t_color *a, t_color *b)
{
    t_color *result;

    result = arena_alloc(*get_arena(), sizeof(t_color));
    result->r = a->r * b->r;
    result->g = a->g * b->g;
    result->b = a->b * b->b;
    return (result);
}