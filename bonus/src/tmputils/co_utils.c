/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:51:27 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/01/29 16:52:21 by ibes-sed         ###   ########.fr       */
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

	cone = malloc(sizeof(t_tcone));
	cone->vertex.x = 0;
	cone->vertex.y = 0;
	cone->vertex.z = 0;
	cone->axis.x = 0;
	cone->axis.y = 0;
	cone->axis.z = 0;
	cone->angle = 0;
	cone->height = 0;
	cone->color.r = 0;
	cone->color.g = 0;
	cone->color.b = 0;
	cone->next = NULL;
	return (cone);
}
