/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:01:10 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/20 10:10:57 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_BONUS_H
# define MATH_BONUS_H
# include "defined_bonus.h"
# include "includes_bonus.h"
# include "objects_bonus.h"

typedef struct s_intersection
{
	t_point		point;
	t_vector	normal;
	t_color		color;
	t_material	material;
	FLOAT		distance;
	FLOAT		t;
	int			id;
	bool		hit;
	FLOAT		u;
	FLOAT		v;
}	t_intersection;

t_vector	vector_add(const t_vector *a, const t_vector *b);
t_vector	vector_sub(const t_vector *a, const t_vector *b);
t_vector	vector_mul(const t_vector *a, const t_vector *b);
t_vector	vector_div(const t_vector *a, const t_vector *b);
t_vector	vector_cross(const t_vector *a, const t_vector *b);
FLOAT		vector_dot(const t_vector *a, const t_vector *b);
FLOAT		vector_length(const t_vector *a);
t_vector	vector_normalize(const t_vector *a);
t_vector	vector_scale(const t_vector *a, FLOAT scale);
t_vector	vector_reflect(const t_vector *incident, const t_vector *normal);

#endif
