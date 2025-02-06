/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:21:08 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/27 16:01:31 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "objects.h"

t_color	color_add(t_color *a, t_color *b);
t_color	color_mul(t_color *a, t_color *b);
t_color	rgbtocolor(int r, int g, int b);
int		colortorgb(t_color *a);
t_color	color_scale(t_color *a, FLOAT scale);

#endif
