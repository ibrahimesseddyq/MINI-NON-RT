/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:58 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/06 21:10:29 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

void	rotate_point_z(t_point *p, t_rotate_point *rp, FLOAT angle)
{
	rp->cos_angle = cos(angle);
	rp->sin_angle = sin(angle);
	rp->new_x = p->x * rp->cos_angle - p->y * rp->sin_angle;
	rp->new_y = p->x * rp->sin_angle + p->y * rp->cos_angle;
	p->x = rp->new_x;
	p->y = rp->new_y;
}

void	rotate_point(t_point *p, t_vector axis, FLOAT angle)
{
	t_rotate_point	rp;
	t_point			temp;

	rp.cos_angle = cos(angle);
	rp.sin_angle = sin(angle);
	rp.dot = axis.x * p->x + axis.y * p->y + axis.z * p->z;
	if (axis.x == 0 && axis.y == 0 && axis.z == 1)
	{
		rotate_point_z(p, &rp, angle);
		return ;
	}
	temp.x = (rp.cos_angle + (1 - rp.cos_angle) * axis.x * axis.x) * p->x
		+ ((1 - rp.cos_angle) * axis.x * axis.y - axis.z * rp.sin_angle) * p->y
		+ ((1 - rp.cos_angle) * axis.x * axis.z + axis.y * rp.sin_angle) * p->z;
	temp.y = ((1 - rp.cos_angle) * axis.y * axis.x
			+ axis.z * rp.sin_angle) * p->x
		+ (rp.cos_angle + (1 - rp.cos_angle) * axis.y * axis.y) * p->y
		+ ((1 - rp.cos_angle) * axis.y * axis.z - axis.x * rp.sin_angle) * p->z;
	temp.z = ((1 - rp.cos_angle) * axis.z * axis.x
			- axis.y * rp.sin_angle) * p->x
		+ ((1 - rp.cos_angle) * axis.z * axis.y + axis.x * rp.sin_angle) * p->y
		+ (rp.cos_angle + (1 - rp.cos_angle) * axis.z * axis.z) * p->z;
	p->x = temp.x;
	p->y = temp.y;
	p->z = temp.z;
}
