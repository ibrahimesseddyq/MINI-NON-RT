/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:05:04 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/25 15:45:24 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/math.h"

t_vector	vector_add(t_vector *a, t_vector *b)
{
	t_vector	res;

	res.x = a->x + b->x;
	res.y = a->y + b->y;
	res.z = a->z + b->z;
	return (res);
}

t_vector	vector_sub(t_vector *a, t_vector *b)
{
	t_vector	res;

	res.x = a->x - b->x;
	res.y = a->y - b->y;
	res.z = a->z - b->z;
	return (res);
}

t_vector	vector_mul(t_vector *a, t_vector *b)
{
	t_vector	res;

	res.x = a->x * b->x;
	res.y = a->y * b->y;
	res.z = a->z * b->z;
	return (res);
}

t_vector	vector_div(t_vector *a, t_vector *b)
{
	t_vector	res;

	res.x = a->x / b->x;
	res.y = a->y / b->y;
	res.z = a->z / b->z;
	return (res);
}

t_vector	vector_cross(t_vector *a, t_vector *b)
{
	t_vector	res;

	res.x = a->y * b->z - a->z * b->y;
	res.y = a->z * b->x - a->x * b->z;
	res.z = a->x * b->y - a->y * b->x;
	return (res);
}
