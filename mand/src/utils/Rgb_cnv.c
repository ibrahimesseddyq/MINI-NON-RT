/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rgb_cnv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:42:01 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/26 11:15:47 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

int	rgb_value(const char *str)
{
	int	nb;

	nb = 0;
	while (*str >= 48 && *str <= 57 && nb <= 255)
		nb = (nb * 10) + (*str++ - 48);
	if (nb > 255 || *str)
		clean_exit("Error: invalid rgb value");
	return (nb);
}
