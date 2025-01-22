/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:09:07 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/22 14:56:10 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../../../minirt_bonus.h"

int process_co(char **inf , t_tscene *t_scene);

void splil_line(const char *line , t_tscene *tscene)
{
    char **elm;
    char **inf;
    int i = 0;
    
    elm = ft_split(line, '\n');
    printf("sefv3\n");

    while (elm[i])
    {
        inf = ft_split(elm[i], ' ');
    printf("sefv4\n");
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
        else if (ft_strcmp(inf[0], "co") == 0 && !process_co(inf ,tscene))
            i++;
        else 
            return (printf("Error \n"),exit(1));
    }
}




