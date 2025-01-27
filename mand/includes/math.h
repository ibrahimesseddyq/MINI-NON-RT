/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:01:10 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/27 11:10:39 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MATH_H
# define MATH_H

# include "defined.h"
# include "includes.h"
# include "objects.h"

typedef struct s_intersection
{
	t_point		point;
	t_vector	normal;
	t_color		color;
	FLOAT		distance;
	FLOAT		t;
	int			id;
	bool		hit;
}	t_intersection;



t_vector	vector_add(const t_vector *a, const t_vector *b);
t_vector	vector_sub(const t_vector *a, const t_vector *b);
t_vector	vector_mul(const t_vector *a, const t_vector *b);
t_vector	vector_div(const t_vector *a, const t_vector *b);
t_vector	vector_cross(const t_vector *a, const t_vector *b);
FLOAT		vector_dot(const t_vector *a, const t_vector *b);
FLOAT		vector_length(const t_vector *a);
t_vector	vector_normalize(const t_vector *a);
t_vector	vector_scale(const t_vector *a, const FLOAT scale);

#endif

