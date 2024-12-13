
#include "../minirt.h"

int	Rgb_value(const char *str)
{
	register  int	nb;

	while (*str >= 48 && *str <= 57 && nb <= 255)
		nb = (nb * 10) + (*str++ - 48);
	if(nb > 255 || *str)
		return (-1);
    return (nb);
}
