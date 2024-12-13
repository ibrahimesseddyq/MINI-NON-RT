
#include "../minirt.h"

int	ft_atoi(const char *str)
{
	register  int	nb;
	register  int	s;
    bool        is_negative;

	nb = 0;
	s = 1;
	if ((*str == 45) || (*str == 43))
		s = 44 - *str++;
    is_negative = s < 0;
	while (*str >= 48 && *str <= 57)
		nb = (nb * 10) + (*str++ - 48);
	if (is_negative == nb * s > 0)
        return (INT_MAX);
    return (nb * s);
}
