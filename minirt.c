/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:41:03 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/20 10:24:00 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_file_ext(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (i < 4 || filename[i - 1] != 't' || filename[i - 2] != 'r'
		|| filename[i - 3] != '.')
		exit(printf("Error: file extension must be .rt\n"));
}

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac != 2)
		return (printf("Error bad arguments\n"));
	check_file_ext(av[1]);
	setup_arena();
	process_flie(av, &scene);
	render(&scene);
	return (SUCCESS);
}
