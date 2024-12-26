/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:52:41 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/26 10:12:17 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tplane* new_plane()
{
    t_tplane *plane;
    
    plane = malloc(sizeof(t_tplane));
    plane->position.x = 0;
    plane->position.y = 0;
    plane->position.z = 0;
    plane->direction.x = 0;
    plane->direction.y = 0;
    plane->direction.z = 0;
    plane->color.r = 0;
    plane->color.g = 0;
    plane->color.b = 0;
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
