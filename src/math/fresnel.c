/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:51:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/23 12:20:48 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../../includes/math.h"

void computeFresnel(FLOAT n1, FLOAT n2, FLOAT cos_i, FLOAT *Kr, FLOAT *Kt) {
    FLOAT r0 = pow((n1 - n2) / (n1 + n2), 2);
    *Kr = r0 + (1 - r0) * pow(1 - cos_i, 5);
}