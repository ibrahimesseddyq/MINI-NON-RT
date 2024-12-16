/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:09:07 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/16 10:32:23 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minirt.h"

int process_A(char **inf)
{
    int x,y,z;
    if (!inf[1] || !inf[2])
        return (1);
   if (!parse_rgb(inf[2], &x, &y, &z) || ft_atof(inf[1]) > 1 || ft_atof(inf[1]) < 0)
        return (1);
    return (0);
}
int process_C(char **inf)
{
    float x,y,z;
    if (!inf[1] || !inf[2] || !inf[3])
        return (1);
    if (!parse_crd(inf[1], &x, &y, &z) ||
     !parse_crd(inf[2], &x, &y, &z) || atoi(inf[3]) > 180 || atoi(inf[3]) < 0
     || x > 1 || x < -1 || y > 1 || y < -1 || z > 1 || z < -1)
        return (1);
    return (0);
}

int process_L(char **inf)
{
    float x,y,z;
    int r,g,b;
    if (!inf[1] || !inf[2] || !inf[3])
        return (1);
    if (!parse_crd(inf[1], &x, &y, &z) ||
     !parse_rgb(inf[3], &r, &g, &b) || ft_atof(inf[2]) > 1 || ft_atof(inf[2]) < 0)
        return (1);
    return (0);
}

int process_sp(char **inf)
{
    float x,y,z;
    int r,g,b;
    if (!inf[1] || !inf[2] || !inf[3])
        return (1);
    if (!parse_crd(inf[1], &x, &y, &z) ||
     !parse_rgb(inf[3], &r, &g, &b) || ft_atof(inf[2]) == (float)INT_MIN)
        return (1);
    return (0);
}

int process_pl(char **inf)
{
    float x,y,z;
    int r,g,b;
     
    if (!inf[1] || !inf[2] || !inf[3])
        return (1);
    if (!parse_crd(inf[1], &x, &y, &z) ||
     !parse_crd(inf[2], &x, &y, &z) ||
     !parse_rgb(inf[3], &r, &g, &b))
        return (1);
    return (0);
}

int process_cy(char **inf)
{
    float x,y,z;
    int r,g,b;
   
    if (!inf[1] || !inf[2] || !inf[3] || !inf[4] || !inf[5])
        return (1);
    if  (!parse_crd(inf[1], &x, &y,&z) ||
     !parse_crd(inf[2], &x, &y, &z) || x < -1 || x > 1 || y < -1 || y > 1 || z < -1 || z > 1 ||
     !parse_rgb(inf[5], &r, &g, &b) || ft_atof(inf[3]) == (float)INT_MIN || ft_atof(inf[4]) == (float)INT_MIN)
        return (1);
    return (0);
}


void splil_line(char line[])
{
    char **elm;
    char **inf;
    int i = 0;
    
    elm = ft_split(line, '\n');
    while (elm[i])
    {
        printf("%s\n", elm[i]);
        inf = ft_split(elm[i], ' ');
        // all of this can be done in one if statement
        if (strcmp(inf[0] ,"A") == 0 && !process_A(inf))
                i++;
        else if (strcmp(inf[0], "C") == 0 && !process_C(inf))
                i++;
        else if (strcmp(inf[0], "L") == 0 && !process_L(inf))
                i++;
        else if (strcmp(inf[0], "sp") == 0 && !process_sp(inf))
                i++;
        else if (strcmp(inf[0], "pl") == 0 && !process_pl(inf))
            i++;
        else if (strcmp(inf[0], "cy") == 0 && !process_cy(inf))
            i++;
        else 
            return (printf("Error \n"),exit(1));
    }
    printf("OK\n");
}

void   process_flie(char **av)
{
    int fd;
    ssize_t ret;
    char buffer[70000];
    
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return (printf("Error\n"),exit(1));
    ret = read(fd, buffer, 70000);
    if (ret == -1)
        return (printf("Error\n"),exit(1));
    buffer[ret + 1] = '\0';
    splil_line(buffer);
    close(fd);
}