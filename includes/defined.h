/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:58:37 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/02 16:15:17 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef DEFINED_H
# define DEFINED_H

# define BUFFER_SIZE 4000
# define WIDTH 2000
# define HEIGHT 1800
# define FLOAT double
# define M_PI 3.14159265358979323846

typedef struct _s_vector
{
    double x;
    double y;
    double z;
} t_vector;

typedef t_vector t_point;
#endif