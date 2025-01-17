/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:58:26 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/11 17:32:38 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../../../minirt.h"

t_tcylinder* new_cylinder()
{
    t_tcylinder *cylinder;
    
    cylinder = malloc(sizeof(t_tcylinder));
    cylinder->position.x = 0;
    cylinder->position.y = 0;
    cylinder->position.z = 0;
    cylinder->direction.x = 0;
    cylinder->direction.y = 0;
    cylinder->direction.z = 0;
    cylinder->diameter = 0;
    cylinder->height = 0;
    cylinder->color.r = 0;
    cylinder->color.g = 0;
    cylinder->color.b = 0;
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