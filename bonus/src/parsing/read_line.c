/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:38:19 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/14 18:15:14 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	int_tsceen(t_tscene *tscene);
bool	mange_line(char *buffer, int *ret, int *backup);
void	restor_line(char **buffer, int *ret, int *backup);

void	ft_check_scene(t_tscene *scene)
{
	if (!scene->is_a_set)
		clean_exit("Error: No ambient light set");
	if (!scene->is_c_set)
		clean_exit("Error: No camera set");
}

void	process_flie(char **av, t_scene *scene)
{
	t_process_file	pi;

	int_tsceen(&pi.tscene);
	pi.fd = open(av[1], O_RDONLY);
	if (pi.fd == -1)
		return (printf("Error can't open %s", *av), clean_exit(""));
	pi.buffer = arena_alloc(*get_arena(), BUFFER_SIZE);
	pi.ret = read(pi.fd, pi.buffer, BUFFER_SIZE);
	while (pi.ret > 0)
	{
		if (!mange_line(pi.buffer, &pi.ret, &pi.backup))
			clean_exit("error file empty or line too long");
		pi.buffer[pi.ret] = '\0';
		splil_line(pi.buffer, &pi.tscene);
		restor_line(&pi.buffer, &pi.ret, &pi.backup);
		pi.ret = read(pi.fd, pi.buffer + pi.backup, BUFFER_SIZE - pi.backup);
		if (pi.ret == 0)
		{
			pi.buffer[pi.backup] = '\0';
			splil_line(pi.buffer, &pi.tscene);
		}
	}
	ft_check_scene(&pi.tscene);
	copy_tscene(&pi.tscene, scene);
	close(pi.fd);
}
