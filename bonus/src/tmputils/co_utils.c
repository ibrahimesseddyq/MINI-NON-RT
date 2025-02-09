/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:51:27 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/09 17:21:20 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	cone_add_front(t_tcone **head, t_tcone *new)
{
	if (!*head)
	{
		*head = new;
		return ;
	}
	new->next = *head;
	*head = new;
}

t_tcone	*new_cone(void)
{
	t_tcone	*cone;

	cone = arena_alloc(*get_arena(), sizeof(t_tcone));
	cone->vertex.x = 0;
	cone->vertex.y = 0;
	cone->vertex.z = 0;
	cone->axis.x = 0;
	cone->axis.y = 0;
	cone->axis.z = 0;
	cone->angle = 0;
	cone->has_color_texture = 1;
	cone->has_bump_texture = 1;
	cone->has_checkerboard = 0;
	cone->height = 0;
	cone->color.r = 0;
	cone->color.g = 0;
	cone->color.b = 0;
	cone->next = NULL;
	return (cone);
}
