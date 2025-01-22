/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:01:10 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/17 15:31:17 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MATH_H
# define MATH_H

#include "defined.h"
#include "includes.h"
#include "objects.h"
typedef struct s_intersection
{
    t_point point;
    t_vector normal;
    t_color color;
    FLOAT distance;
    FLOAT t;
    int id;
    bool hit;
    FLOAT u;
    FLOAT v;
} t_intersection;



t_vector vector_add(t_vector *a, t_vector *b);
t_vector vector_sub(t_vector *a, t_vector *b);
t_vector vector_mul(t_vector *a, t_vector *b);
t_vector vector_div(t_vector *a, t_vector *b);
t_vector vector_cross(t_vector *a, t_vector *b);
FLOAT vector_dot(t_vector *a, t_vector *b);
FLOAT vector_length(t_vector *a);
t_vector vector_normalize(t_vector *a);
t_vector vector_scale(t_vector *a, FLOAT scale);

#endif

