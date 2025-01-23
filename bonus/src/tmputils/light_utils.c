/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:51:47 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/23 14:00:26 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void light_add_front(t_tlight **head, t_tlight *new)
{
  if (!*head)
  {
    *head = new;
    return;
  }
    new->next = *head;
    *head = new;
}
t_tlight *new_light()
{
    t_tlight *tlight;
    
    tlight = malloc(sizeof(t_light));
    tlight->position.x = 0;
    tlight->position.y = 0;
    tlight->position.z = 0;
    tlight->bratio = 0;
    tlight->color.r = 0;
    tlight->color.g = 0;
    tlight->color.b = 0;
    tlight->next = NULL;
    return (tlight);
}