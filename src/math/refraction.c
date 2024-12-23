/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:11:19 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/23 12:11:32 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/math.h"

t_vector *computeRefractionRay(t_vector *incident, t_vector *normal, FLOAT n1, FLOAT n2)
{
    t_vector refraction;
    FLOAT n = n1 / n2;
    FLOAT cosI = -vec_dot(normal, incident);
    FLOAT sinT2 = n * n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0)
        return NULL;
    FLOAT cosT = sqrt(1.0 - sinT2);
    refraction.x = n * incident->x + (n * cosI - cosT) * normal->x;
    refraction.y = n * incident->y + (n * cosI - cosT) * normal->y;
    refraction.z = n * incident->z + (n * cosI - cosT) * normal->z;
    return vec_normalize(&refraction);
}