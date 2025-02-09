/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:10:28 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/09 17:04:32 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAX 2147483647
# include "./../../../minirt_bonus.h"

int	ft_atoi(const char *str)
{
	long long	nb;
	long		s;

	nb = 0;
	s = 1;
	while ((*str == 32) || ((*str >= 9) && (*str <= 13)))
		str++;
	if ((*str == 45) || (*str == 43))
		s = 44 - *str++;
	while (*str >= 48 && *str <= 57)
	{
		if (nb > MAX)
			clean_exit("Error: Integer overflow");
		nb = (nb * 10) + (*str++ - 48);
	}
	printf("nb = %lld\n", nb);
	return (s * nb);
}
