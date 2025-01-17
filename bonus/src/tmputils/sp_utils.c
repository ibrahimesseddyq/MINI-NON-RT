/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:02:07 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/26 10:12:42 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tsphere* new_sphere()
{
    t_tsphere *sphere;
    
    sphere = malloc(sizeof(t_tsphere));
    sphere->position.x = 0;
    sphere->position.y = 0;
    sphere->position.z = 0;
    sphere->diameter = 0;
    sphere->color.r = 0;
    sphere->color.g = 0;
    sphere->color.b = 0;
    sphere->next = NULL;
    return (sphere);
}

void sphere_add_front(t_tsphere **head, t_tsphere *new)
{
  if (!*head)
  {
    *head = new;
    return;
  }
    new->next = *head;
    *head = new;
}
