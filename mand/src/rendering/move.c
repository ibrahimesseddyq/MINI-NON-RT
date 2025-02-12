/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:33 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/12 15:31:35 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

void	move_light_or_camera(int *keys, t_scene *scene)
{
	if ((char)keys[1] == 'c')
		move_camera(keys, &scene->camera);
	else
		move_light(keys, &scene->light);
	return ;
}
