/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rgb_cnv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:42:01 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/16 09:55:43 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	Rgb_value(const char *str)
{
	register  int	nb;

	nb = 0;
	while (*str >= 48 && *str <= 57 && nb <= 255)
		nb = (nb * 10) + (*str++ - 48);
	if(nb > 255 || *str)
		return (-1);
    return (nb);
}