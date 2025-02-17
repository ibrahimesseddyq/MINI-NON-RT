/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:43:06 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/13 15:08:54 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

int	hook(t_scene *scene)
{
	mlx_destroy_window(scene->mlx, scene->win);
	mlx_clear_window(scene->mlx, scene->win);
	clean_exit("");
	return (0);
}
