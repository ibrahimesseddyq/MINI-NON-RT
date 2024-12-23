/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:51:36 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/23 12:11:07 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/math.h"
#include "./../../includes/memory.h"


t_vector *computeReflectionRay(t_vector *incident, t_vector *normal) 
{
    t_vector reflection;
    FLOAT dot = vec_dot(incident, normal);
    reflection.x = incident->x - 2 * dot * normal->x;
    reflection.y = incident->y - 2 * dot * normal->y;
    reflection.z = incident->z - 2 * dot * normal->z;
    return vec_normalize(&reflection);
}