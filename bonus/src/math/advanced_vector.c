/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:52 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/11 20:00:26 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/math.h"

FLOAT	vector_dot(const t_vector *a, const t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

FLOAT	vector_length(const t_vector *a)
{
	return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z));
}

t_vector	vector_normalize(const t_vector *a)
{
	FLOAT		len;
	t_vector	res;

	len = vector_length(a);
	res.x = a->x / len;
	res.y = a->y / len;
	res.z = a->z / len;
	return (res);
}

t_vector	vector_scale(const t_vector *a, FLOAT scale)
{
	t_vector	res;

	res.x = a->x * scale;
	res.y = a->y * scale;
	res.z = a->z * scale;
	return (res);
}

t_vector	vector_reflect(const t_vector *incident, const t_vector *normal)
{
	FLOAT		dot_product;
	t_vector	scaled_normal;
	t_vector	reflection;

	dot_product = vector_dot(normal, incident);
	scaled_normal = vector_scale(normal, 2.0 * dot_product);
	reflection = vector_sub(incident, &scaled_normal);
	return (reflection);
}
