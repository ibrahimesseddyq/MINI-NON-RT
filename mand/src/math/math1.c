/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:27:47 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/25 13:50:21 by sessarhi         ###   ########.fr       */
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

	len = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	len = 1 / len;
	res.x = a->x * len;
	res.y = a->y * len;
	res.z = a->z * len;
	return (res);
}

t_vector	vector_scale(const t_vector *a, const FLOAT scale)
{
	t_vector	res;

	res.x = a->x * scale;
	res.y = a->y * scale;
	res.z = a->z * scale;
	return (res);
}
