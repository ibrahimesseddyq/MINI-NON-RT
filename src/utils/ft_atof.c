/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:42:24 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/16 10:30:36 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minirt.h"

static bool check_fp_err(char *str)
{
    int i;
    bool flag;
    
    i = 0;
    flag = false;
    while (str[i])
    {
        if (str[i] == '.')
        {
            if (flag)
                return (false);
            else if (str[i + 1] == '\0' || str[0] == '.')
                return (false);
            flag = true;
        }
        i++;
    }
    return (true);
}

float	ft_atof(char *str)
{
    float result;
    int sign;
    float decimal;

    result = 0.0;
    sign = 1;
    decimal = 0.1;
    if (!check_fp_err(str))
        return ((float)INT_MIN); //temproary error return value
    if (*str == '-')
		sign = *str++ - 46;
	while (*str >= '0' && *str <= '9')
        result = result * 10 + *str++ - '0';
    if (*str == '.')
        str++;
    if ((*str < '0' || *str > '9') && *str != '\0')
        return ((float)INT_MIN); //temproary error return value
    while (*str >= '0' && *str <= '9')
    {
        result += ((*str++ - '0') * decimal);
        decimal *= 0.1;
    }
    if (*str)
        return ((float)INT_MIN); //temproary error return value
    return (result * sign);
}
