#include "./../../includes/math.h"
#include "./../../includes/memory.h"

t_point *create_point(FLOAT x, FLOAT y, FLOAT z)
{
    t_point *p;

    // p = arena_alloc(*get_arena(), sizeof(t_point));
    p = malloc(sizeof(t_point));

    p->x = x;
    p->y = y;
    p->z = z;
    return (p);
}