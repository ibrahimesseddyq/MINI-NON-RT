/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:10:28 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/29 14:11:57 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAX 922337203685477580

int	ft_atoi(const char *str)
{
	register  long long	nb;
	register  long	s;

	nb = 0;
	s = 1;
	while ((*str == 32) || ((*str >= 9) && (*str <= 13)))
		str++;
	if ((*str == 45) || (*str == 43))
		s = 44 - *str++;
	while (*str >= 48 && *str <= 57)
	{
		if ((nb > MAX) || ((nb == MAX) && ((*str - 48) >= 8)))
			return (-0.5 * (s + 1));
		nb = (nb * 10) + (*str++ - 48);
	}
	return (s * nb);
}