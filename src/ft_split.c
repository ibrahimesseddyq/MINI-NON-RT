/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:26:54 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/13 19:05:09 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static size_t	ft_countwords(const char *s, size_t *i, char c)
{
    size_t	len;

    len = 0;
    *i = 0;
    while (*s)
    {
        if (*s != c && *s)
        {
            len++;
            while (*s && *s != c)
            {
                s++;
                (*i)++;
            }
            if (*s)
                (*i)++;
        }
        while (*s == c && *s)
            s++;
    }
    return (len);
}

char	**ft_split(char const *s, char c)
{
    char	**str;
    char	*tmp;
    size_t	i;
    size_t	len;

    if (!s)
        return (NULL);
    len = sizeof(char *) *( ft_countwords(s, &i, c) + 1);
    str = malloc(len + (i + 1));
    if (!str)
        return (NULL);
    tmp = (char *)str + len + 1;
    i = 0;
    while (*s)
    {
        if (*s != c && *s)
        {
            str[i++] = tmp;
            while (*s && *s != c)
                *tmp++ = *s++;
            if (*s && *s == c)
                *tmp++ = '\0' , s++;
        }
        while (*s == c && *s)
            s++;
    }
    return (str[i] = NULL, str);
}
