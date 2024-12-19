/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:52:41 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/18 13:57:38 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tplane* new_plane()
{
    t_tplane *plane;
    
    plane = malloc(sizeof(t_tplane));
    plane->x = 0;
    plane->y = 0;
    plane->z = 0;
    plane->vx = 0;
    plane->vy = 0;
    plane->vz = 0;
    plane->r = 0;
    plane->g = 0;
    plane->b = 0;
    plane->next = NULL;
    return (plane);
}

void plane_add_front(t_tplane **head, t_tplane *new)
{
  if (!*head)
  {
    *head = new;
    return;
  }
    new->next = *head;
    *head = new;
}
