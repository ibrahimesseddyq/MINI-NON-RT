#include "./../../../minirt_bonus.h"

t_vector	point_to_vector(t_point *point)
{
	t_vector	vector;

	vector.x = point->x;
	vector.y = point->y;
	vector.z = point->z;
	return (vector);
}

void	init_cone_vars(t_hit_cone_intersection *inter, t_point *vertex,
		t_vector *axis, t_ray *ray, double angle)
{
	inter->oc = vector_sub(&ray->origin, vertex);
	inter->cos2 = cos(angle) * cos(angle);
	inter->sin2 = sin(angle) * sin(angle);
	inter->a = vector_dot(&ray->direction, axis)
		* vector_dot(&ray->direction, axis) - inter->cos2;
	inter->b = 2.0 * (vector_dot(&ray->direction, axis)
			* vector_dot(&inter->oc, axis)
			- vector_dot(&ray->direction, &inter->oc) * inter->cos2);
	inter->c = vector_dot(&inter->oc, axis) * vector_dot(&inter->oc, axis)
		- vector_dot(&inter->oc, &inter->oc) * inter->cos2;
}

double	get_intersection_t(t_hit_cone_intersection *inter)
{
	inter->discriminant = inter->b * inter->b - 4 * inter->a * inter->c;
	if (inter->discriminant < 0)
		return (-1);
	inter->t1 = (-inter->b - sqrt(inter->discriminant)) / (2.0 * inter->a);
	inter->t2 = (-inter->b + sqrt(inter->discriminant)) / (2.0 * inter->a);
	if (inter->t1 > 0 && inter->t2 > 0)
		inter->t = fmin(inter->t1, inter->t2);
	else if (inter->t1 > 0)
		inter->t = inter->t1;
	else if (inter->t2 > 0)
		inter->t = inter->t2;
	else
		return (-1);
	return (inter->t);
}

int	check_height_bounds(t_hit_cone_intersection *inter, t_point *vertex,
		t_vector *axis, t_ray *ray)
{
	inter->scaled_v = vector_scale(&ray->direction, inter->t);
	inter->hit_point = vector_add(&ray->origin, &inter->scaled_v);
	inter->cone_to_hit = vector_sub(&inter->hit_point, vertex);
	if (vector_dot(&inter->cone_to_hit, axis) < 0
		|| vector_dot(&inter->cone_to_hit, axis) > vector_length(axis))
		return (0);
	return (1);
}
