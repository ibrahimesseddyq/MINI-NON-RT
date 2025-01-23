/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:26:54 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/11 17:32:22 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

//ths function is ugly 
static size_t    ft_countwords(const char *s, size_t *i, char c)
{
    size_t    len;

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
//to fix the fucking norm pass len by address 
char    **ft_split(char const *s, char c)
{
    char    **str;
    char    *tmp;
    size_t    i;
    size_t    len;

    if (!s)
        return (NULL);
    len = sizeof(char *) * (ft_countwords(s, &i, c) + 1);
    str = malloc(len + i + 1);
    if (!str)
        return (NULL);
    tmp = (char *)str + len;
    i = 0;
    while (*s)
    {
        if (*s != c && *s)
        {
            str[i++] = tmp;
            while (*s && *s != c)
                *tmp++ = *s++;
            *tmp++ = '\0';
        }
        while (*s == c && *s)
            s++;
    }
    return (str[i] = NULL, str);
}
