/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:37 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/10 19:04:55 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

t_vector	get_shadow_ray_origin(t_vector *normal,
	t_vector *point, bool is_inside)
{
	t_vector	offset;
	FLOAT		direction;

	if (is_inside)
		direction = -1.0;
	else
		direction = 1.0;
	offset = vector_scale(normal, SHADOW_BIAS * direction);
	return (vector_add(point, &offset));
}

t_light_calc	calculate_light_contribution(t_light *light,
		t_light_params *params)
{
	t_calculate_light_contribution	li;

	li.sub_vec = vector_sub(&light->position,
			&params->intersection_point);
	li.light_dir = vector_normalize(&li.sub_vec);
	li.diff = fmax(0.0, vector_dot(&params->surface_normal, &li.light_dir));
	li.diff *= light->bratio;
	li.result.diffuse
		= color_scale(&light->color, li.diff * params->material.kd);
	li.added_vec = vector_add(&li.light_dir, &params->view_dir);
	li.half_vector = vector_normalize(&li.added_vec);
	li.spec
		= pow(fmax(0.0, vector_dot(&params->surface_normal, &li.half_vector)),
			params->material.n);
	li.spec *= light->bratio;
	li.result.specular
		= color_scale(&light->color, li.spec * params->material.ks);
	return (li.result);
}

bool	process_shadow_ray(t_scene *scene, t_vector *light_pos,
	t_intersection *isect, bool is_inside)
{
	t_ray		shadow_ray;
	t_vector	ray_origin;
	t_vector	ray_direction;

	ray_origin = get_shadow_ray_origin(&isect->normal,
			&isect->point, is_inside);
	shadow_ray.origin = ray_origin;
	ray_direction = vector_sub(light_pos, &ray_origin);
	shadow_ray.direction = vector_normalize(&ray_direction);
	return (check_shadow(scene, &shadow_ray, isect));
}

int	pixel_color(t_scene *scene, t_intersection *isect, t_ray *ray)
{
	t_pixel_info	pinfos;

	pinfos.scaled_vec = vector_scale(&ray->direction, -1);
	pinfos.params.view_dir = vector_normalize(&pinfos.scaled_vec);
	pinfos.ambient = color_scale(&scene->ambient.color,
			scene->ambient.ratio * isect->material.ka);
	calculate_surface_properties(scene, isect, &pinfos.texture_color,
		&pinfos.params.surface_normal);
	pinfos.params.intersection_point = isect->point;
	pinfos.params.material = isect->material;
	pinfos.final_color = process_lights(scene, isect, ray, &pinfos.params);
	pinfos.final_color = color_add(&pinfos.ambient, &pinfos.final_color);
	pinfos.final_color = color_mul(&pinfos.final_color, &pinfos.texture_color);
	return (colortorgb(&pinfos.final_color));
}

t_color	process_lights(t_scene *scene, t_intersection *isect,
	t_ray *ray, t_light_params *params)
{
	t_light_calc	light_calc;
	t_color			total_diffuse;
	t_color			total_specular;
	int				i;

	total_diffuse = (t_color){0};
	total_specular = (t_color){0};
	i = -1;
	while (++i < scene->light_count)
	{
		if (process_shadow_ray(scene, &scene->light[i].position,
				isect, vector_dot(&isect->normal, &ray->direction) > 0))
			continue ;
		light_calc = calculate_light_contribution(&scene->light[i], params);
		total_diffuse = color_add(&total_diffuse, &light_calc.diffuse);
		total_specular = color_add(&total_specular, &light_calc.specular);
	}
	return (color_add(&total_diffuse, &total_specular));
}
