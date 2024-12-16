/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:16:40 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/16 16:45:02 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
#include <string.h>
#include "./includes/objects.h"


#define BUFFER_SIZE 1000000

// Parsing
bool  parse_crd(const char *str,float *x ,float *y ,float *z);
bool	parse_rgb(const char *str ,int *r ,int *g ,int *b);


// Utils
char    **ft_split(char const *s, char c);
float	ft_atof(char *str);
int	Rgb_value(const char *str);
void   process_flie( char **av);


#endif