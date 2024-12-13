#include "../minirt.h"

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
        return ((float)INT_MIN);
    return (result * sign);
}
