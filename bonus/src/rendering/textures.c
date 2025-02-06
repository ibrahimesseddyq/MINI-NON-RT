/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:10 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/06 18:30:23 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

t_color	sample_texture(t_texture *texture, FLOAT u, FLOAT v);

t_vector	calculate_tangent(t_vector *normal)
{
	t_vector	tangent;

	if (fabs(normal->y) < 0.99)
		tangent = vector_cross(normal, &(t_vector){0, 1, 0});
	else
		tangent = vector_cross(normal, &(t_vector){1, 0, 0});
	return (vector_normalize(&tangent));
}

t_derivatives	sample_bump_derivatives(t_bump_params *params)
{
	FLOAT			step;
	t_color			c;
	t_color			cx;
	t_color			cy;
	t_derivatives	result;

	step = 1.0 / params->bump_map->width;
	c = sample_texture(params->bump_map, params->u, params->v);
	cx = sample_texture(params->bump_map, params->u + step, params->v);
	cy = sample_texture(params->bump_map, params->u, params->v + step);
	result.dx = (cx.r - c.r) * params->strength;
	result.dy = (cy.r - c.r) * params->strength;
	return (result);
}

t_vector	calculate_bitangent(t_vector *tangent, t_vector *normal)
{
	t_vector	bitangent;

	bitangent = vector_cross(tangent, normal);
	return (vector_normalize(&bitangent));
}

t_vector	modify_normal(t_normal_modify *params)
{
	t_vector	modified_normal;
	t_vector	scaled_tan;
	t_vector	scaled_bitan;
	t_vector	vec_addition;

	modified_normal = *(params->original_normal);
	scaled_tan = vector_scale(params->tangent, params->dx);
	scaled_bitan = vector_scale(params->bitangent, params->dy);
	modified_normal = vector_add(&modified_normal, &scaled_tan);
	vec_addition = vector_add(&modified_normal, &scaled_bitan);
	return (vector_normalize(&vec_addition));
}

t_vector	calculate_bump_normal(t_texture *bump_map, FLOAT u, FLOAT v,
					t_vector *original_normal)
{
	t_bump_params	bump_params;
	t_derivatives	derivs;
	t_vector		tangent;
	t_vector		bitangent;

	if (!bump_map->addr)
		return (*original_normal);
	bump_params = (t_bump_params){u, v, 1.0, bump_map};
	derivs = sample_bump_derivatives(&bump_params);
	tangent = calculate_tangent(original_normal);
	bitangent = calculate_bitangent(&tangent, original_normal);
	return (modify_normal(&(t_normal_modify){
			original_normal,
			&tangent,
			&bitangent,
			derivs.dx,
			derivs.dy
		}));
}
