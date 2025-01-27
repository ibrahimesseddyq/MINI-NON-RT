#include "./../../../minirt_bonus.h"

double	hit_cone(t_point *vertex, t_vector *axis, double angle, t_ray *ray)
{
	t_hit_cone_intersection	inter;
	double					t;

	init_cone_vars(&inter, vertex, axis, ray, angle);
	t = get_intersection_t(&inter);
	if (t < 0 || !check_height_bounds(&inter, vertex, axis, ray))
		return (-1);
	return (t);
}

void	calculate_cone_normal(t_scene *scene,
			t_intersection *intersection, t_cone_intersection	*inter, int i)
{
	inter->cone_to_point
		= vector_sub(&intersection->point, &scene->cone[i].vertex);
	inter->axis_scaled
		= vector_scale(&scene->cone[i].axis,
			vector_dot(&inter->cone_to_point, &scene->cone[i].axis));
	inter->subs_vec
		= vector_sub(&inter->cone_to_point, &inter->axis_scaled);
	intersection->normal = vector_normalize(&inter->subs_vec);
}

bool	cone_intersection(t_scene *scene,
		t_intersection *intersection, t_ray *ray)
{
	int					i;
	FLOAT				t;
	t_vector			tmp;
	t_cone_intersection	inter;

	i = scene->cone_count;
	while (i--)
	{
		t = hit_cone(&scene->cone[i].vertex, &scene->cone[i].axis,
				scene->cone[i].angle, ray);
		if (t > 0 && t < intersection->distance)
		{
			intersection->hit = true;
			intersection->id = scene->cone[i].id;
			intersection->distance = t;
			intersection->color = scene->cone[i].color;
			tmp = vector_scale(&ray->direction, t);
			intersection->point
				= vector_add(&ray->origin, &tmp);
			calculate_cone_normal(scene, intersection, &inter, i);
		}
	}
	return (intersection->hit);
}
