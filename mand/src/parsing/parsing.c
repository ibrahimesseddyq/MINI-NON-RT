/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:09:07 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/21 16:44:19 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../../../minirt.h"

void splil_line(const char *line , t_tscene *tscene)
{
    char **elm;
    char **inf;
    int i = 0;
    
    elm = ft_split(line, '\n');
    while (elm[i])
    {
        inf = ft_split(elm[i], ' ');
        if (ft_strcmp(inf[0] ,"A") == 0 && !process_A(inf , tscene))
                i++;
        else if (ft_strcmp(inf[0], "C") == 0 && !process_C(inf  ,tscene))
                i++;
        else if (ft_strcmp(inf[0], "L") == 0 && !process_L(inf ,tscene))
                i++;
        else if (ft_strcmp(inf[0], "sp") == 0 && !process_sp(inf ,tscene))
                i++;
        else if (ft_strcmp(inf[0], "pl") == 0 && !process_pl(inf ,tscene))
            i++;
        else if (ft_strcmp(inf[0], "cy") == 0 && !process_cy(inf ,tscene))
            i++;
        else 
            return (printf("Error \n"),exit(1));
    }
}




