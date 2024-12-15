/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:42:24 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/15 12:16:08 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minirt.h"

float	ft_atof(char *str)
{
    float result;
    int sign;
    float decimal;

    result = 0;
    sign = 1;
    decimal = 0.1;
    if ((*str == 45) || (*str == 43))
		sign = 44 - *str++;
	while (*str >= '0' && *str <= '9')
        result = result * 10 + *str++ - '0';
    if (*str == '.')
        str++;
    while (*str >= '0' && *str <= '9')
    {
        result += ((*str++ - '0') * decimal);
        decimal *= 0.1;
    }
    if (*str)
        return ((float)INT_MIN); //temproary error return value
    return (result * sign);
}
