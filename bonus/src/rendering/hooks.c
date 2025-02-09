/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:19 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/08 19:35:41 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

int	key_hook(int keycode, t_scene *scene)
{
	return (0);
}

int	hook(t_scene *scene)
{
	mlx_destroy_window(scene->mlx, scene->win);
	clean_exit("");
	return (0);
}
