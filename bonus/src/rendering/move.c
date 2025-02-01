/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:33 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/01/28 22:23:34 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	move_light_or_camera(int *keys, t_scene *scene)
{
	int	i;
	int	obj_id;

	if ((char)keys[1] == 'c')
		move_camera(keys, &scene->camera);
	else
	{
		obj_id = my_atoi(keys, 2);
		while (i < scene->light_count)
		{
			if (scene->light[i].id == obj_id)
				move_light(keys, &scene->light[i]);
			i++;
		}
	}
	return ;
}
