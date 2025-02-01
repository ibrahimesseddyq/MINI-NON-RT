/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:27:41 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/01/29 17:35:54 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

// FLOAT	calculate_body_intersection(const t_ray *ray,
// 		const t_cylinder *cylinder)
// {
// 	t_body_intersection	bi;

// 	bi.oc = vector_sub(&ray->origin, &cylinder->position);
// 	bi.dir_dot_dir = vector_dot(&ray->direction, &cylinder->direction);
// 	bi.oc_dot_dir = vector_dot(&bi.oc, &cylinder->direction);
// 	bi.a = vector_dot(&ray->direction, &ray->direction)
// 		- pow(bi.dir_dot_dir, 2);
// 	if (fabs(bi.a) < EPSILON)
// 		return (-1);
// 	bi.b = 2 * (vector_dot(&ray->direction, &bi.oc)
// 			- bi.dir_dot_dir * bi.oc_dot_dir);
// 	bi.c = vector_dot(&bi.oc, &bi.oc)
// 		- pow(bi.oc_dot_dir, 2) - pow(cylinder->diameter / 2, 2);
// 	bi.discriminant = bi.b * bi.b - 4 * bi.a * bi.c;
// 	if (bi.discriminant < 0)
// 		return (-1);
// 	bi.sqrt_discriminant = sqrt(bi.discriminant);
// 	bi.t1 = (-bi.b - bi.sqrt_discriminant) / (2.0 * bi.a);
// 	if (bi.t1 > EPSILON)
// 		return (bi.t1);
// 	bi.t2 = (-bi.b + bi.sqrt_discriminant) / (2.0 * bi.a);
// 	if (bi.t2 > EPSILON)
// 		return (bi.t2);
// 	return (-1);
// }

bool	is_within_cylinder_height(const t_vector *point,
	const t_cylinder *cylinder)
{
	t_vector	cp;
	FLOAT		height;

	height = vector_dot(&cp, &cylinder->direction);
	cp = vector_sub(point, &cylinder->position);
	return (height >= 0 && height <= cylinder->height);
}

FLOAT	calculate_body_intersection(const t_ray *ray,
		const t_cylinder *cylinder)
{
	t_body_intersection	bi;

	bi.oc = vector_sub(&ray->origin, &cylinder->position);
	bi.dir_dot_dir = vector_dot(&ray->direction, &cylinder->direction);
	bi.oc_dot_dir = vector_dot(&bi.oc, &cylinder->direction);
	bi.a = vector_dot(&ray->direction, &ray->direction)
		- pow(bi.dir_dot_dir, 2);
	if (fabs(bi.a) < EPSILON)
		return (-1);
	bi.b = 2 * (vector_dot(&ray->direction, &bi.oc)
			- bi.dir_dot_dir * bi.oc_dot_dir);
	bi.c = vector_dot(&bi.oc, &bi.oc)
		- pow(bi.oc_dot_dir, 2) - pow(cylinder->diameter / 2, 2);
	bi.discriminant = bi.b * bi.b - 4 * bi.a * bi.c;
	if (bi.discriminant < 0)
		return (-1);
	bi.sqrt_discriminant = sqrt(bi.discriminant);
	bi.t1 = (-bi.b - bi.sqrt_discriminant) / (2.0 * bi.a);
	if (bi.t1 > EPSILON)
		return (bi.t1);
	bi.t2 = (-bi.b + bi.sqrt_discriminant) / (2.0 * bi.a);
	if (bi.t2 > EPSILON)
		return (bi.t2);
	return (-1);
}
