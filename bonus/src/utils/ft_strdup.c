/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:08:11 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/13 13:51:00 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

static size_t	ft_strlen(const char *s)
{
	char	*str;

	str = (char *)s;
	while (*str)
		str++;
	return (str - s);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = arena_alloc(*get_arena(), sizeof(char ) * (ft_strlen(str) + 1));
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
