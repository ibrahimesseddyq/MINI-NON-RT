/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:52:09 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/13 11:43:19 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac != 2)
		return (printf("Error bad arguments\n"));
	setup_arena();
	process_flie(av, &scene);
	render(&scene);
	return (SUCCESS);
}
