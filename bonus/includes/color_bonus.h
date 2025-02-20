/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:21:08 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/20 10:10:41 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_BONUS_H
# define COLOR_BONUS_H
# include "objects_bonus.h"

t_color	color_add(t_color *a, t_color *b);
t_color	color_mul(t_color *a, t_color *b);
t_color	rgbtocolor(int r, int g, int b);
int		colortorgb(t_color *a);
t_color	color_scale(t_color *a, FLOAT scale);
#endif
