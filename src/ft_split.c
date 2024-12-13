/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:26:54 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/13 11:28:31 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	ft_countwords(char *s, char **new, char c)
{
    int	len;
    char	*tmp;
    char	*buffer;

    buffer = (char *)malloc(ft_strlen(s) + 1);
    if (!buffer)
        return (-1);
    tmp = buffer;
    len = 0;
    while (*s)
    {
        if (*s != c && *s)
        {
            len++;
            while (*s && *s != c)
                *tmp++ = *s++;
            *tmp++ = '\0';
        }
        while (*s == c && *s)
            s++;
    }
    return (*new = buffer, len);
}

char	**ft_split(char const *s, char c)
{
    char	**str;
    char	*tmp;
    size_t	i;
    size_t	len;

    if (!s)
        return (NULL);
    len = ft_countwords((char *)s, &tmp, c);
    str = malloc(sizeof(char *) * (len + 1));
    if (!str)
        return (NULL);
    i = -1;
    while (++i < len)
    {
        str[i] = ft_strdup(tmp);
        tmp += ft_strlen(tmp) + 1;

    }
    return ( str[i] = NULL, str);
}

// this need to be reimplemented 