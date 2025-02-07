/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpobjects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:24:29 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/06 22:40:10 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TMPOBJECTS_H
# define TMPOBJECTS_H
# include "includes.h"

t_tsphere	*new_sphere(void);
t_tcylinder	*new_cylinder(void);
t_tplane	*new_plane(void);
t_tcone		*new_cone(void);
void		cylinder_add_front(t_tcylinder **cylinder, t_tcylinder *new);
void		plane_add_front(t_tplane **plane, t_tplane *new);
void		sphere_add_front(t_tsphere **sphere, t_tsphere *new);
void		light_add_front(t_tlight **head, t_tlight *new);
void		cone_add_front(t_tcone **head, t_tcone *new);
t_tlight	*new_light(void);

#endif