/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:58:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/18 13:58:45 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minirt.h"

t_tcylinder* new_cylinder()
{
    t_tcylinder *cylinder;
    
    cylinder = malloc(sizeof(t_tcylinder));
    cylinder->x = 0;
    cylinder->y = 0;
    cylinder->z = 0;
    cylinder->vx = 0;
    cylinder->vy = 0;
    cylinder->vz = 0;
    cylinder->diameter = 0;
    cylinder->r = 0;
    cylinder->g = 0;
    cylinder->b = 0;
    cylinder->next = NULL;
    return (cylinder);
}

void cylinder_add_front(t_tcylinder **head, t_tcylinder *new)
{
  if (!*head)
  {
    *head = new;
    return;
  }
    new->next = *head;
    *head = new;
}