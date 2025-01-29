/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:29 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/01/28 22:23:30 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	move_camera(int *keys, t_camera *camera)
{
	if (keys[0] == LEFT_ROW_KEY)
		camera->position.x--;
	else if (keys[0] == RIGHT_ROW_KEY)
		camera->position.x++;
	else if (keys[0] == UPPER_ROW_KEY)
		camera->position.y++;
	else if (keys[0] == DOWN_ROW_KEY)
		camera->position.y--;
	else if (keys[0] == M_KEY)
		camera->position.z--;
	else if (keys[0] == N_KEY)
		camera->position.z++;
}

void	move_light(int *keys, t_light *light)
{
	if (keys[0] == LEFT_ROW_KEY)
		light->position.x--;
	else if (keys[0] == RIGHT_ROW_KEY)
		light->position.x++;
	else if (keys[0] == UPPER_ROW_KEY)
		light->position.y++;
	else if (keys[0] == DOWN_ROW_KEY)
		light->position.y--;
	else if (keys[0] == M_KEY)
		light->position.z--;
	else if (keys[0] == N_KEY)
		light->position.z++;
}

void	move_cylinder(int *keys, t_cylinder *cylinder)
{
	if (keys[0] == LEFT_ROW_KEY)
		cylinder->position.x--;
	else if (keys[0] == RIGHT_ROW_KEY)
		cylinder->position.x++;
	else if (keys[0] == UPPER_ROW_KEY)
		cylinder->position.y++;
	else if (keys[0] == DOWN_ROW_KEY)
		cylinder->position.y--;
	else if (keys[0] == M_KEY)
		cylinder->position.z--;
	else if (keys[0] == N_KEY)
		cylinder->position.z++;
}

void	move_plane(int *keys, t_plane *plane)
{
	if (keys[0] == LEFT_ROW_KEY)
		plane->position.x--;
	else if (keys[0] == RIGHT_ROW_KEY)
		plane->position.x++;
	else if (keys[0] == UPPER_ROW_KEY)
		plane->position.y++;
	else if (keys[0] == DOWN_ROW_KEY)
		plane->position.y--;
	else if (keys[0] == M_KEY)
		plane->position.z--;
	else if (keys[0] == N_KEY)
		plane->position.z++;
}

void	move_sphere(int *keys, t_sphere *sphere)
{
	if (keys[0] == LEFT_ROW_KEY)
		sphere->position.x--;
	else if (keys[0] == RIGHT_ROW_KEY)
		sphere->position.x++;
	else if (keys[0] == UPPER_ROW_KEY)
		sphere->position.y++;
	else if (keys[0] == DOWN_ROW_KEY)
		sphere->position.y--;
	else if (keys[0] == M_KEY)
		sphere->position.z--;
	else if (keys[0] == N_KEY)
		sphere->position.z++;
}
