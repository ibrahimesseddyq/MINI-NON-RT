/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:38:19 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/14 18:16:23 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

static void	int_tsceen(t_tscene *tscene)
{
	tscene->cylinder = NULL;
	tscene->plane = NULL;
	tscene->sphere = NULL;
	tscene->plane_size = 0;
	tscene->cylinder_size = 0;
	tscene->sphere_size = 0;
	tscene->is_c_set = false;
	tscene->is_a_set = false;
	tscene->is_l_set = false;
	tscene->camera.position.x = 0;
	tscene->camera.position.y = 0;
	tscene->camera.position.z = 0;
	tscene->camera.direction.x = 0;
	tscene->camera.direction.y = 0;
	tscene->camera.direction.z = 0;
}

static bool	mange_line(char *buffer, int *ret, int *backup)
{
	int	i;

	i = *ret;
	buffer[i--] = '\0';
	while (i > 0 && buffer[i] != '\n')
		i--;
	if (i == 0 && buffer[i] != '\n')
		return (false);
	*backup = *ret - i;
	buffer[i] = '\0';
	*ret = i;
	return (true);
}

static void	restor_line(char **buffer, int *ret, int *backup)
{
	int		i;
	char	*buf;

	buf = *buffer;
	i = 0;
	*ret += 1;
	while (buf[*ret] != '\0')
	{
		buf[i] = buf[*ret];
		i++;
		(*ret)++;
	}
	*backup = i;
}

void	prep_read(int *fd, char **buffer, char *file)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		printf("Error can't open %s", file);
		clean_exit("");
	}
	*buffer = arena_alloc(*get_arena(), BUFFER_SIZE);
	if (!*buffer)
		clean_exit("Error malloc");
}

void	process_flie(char **av, t_scene *scene)
{
	int			fd;
	int			ret;
	char		*buffer;
	t_tscene	tscene;
	int			backup;

	int_tsceen(&tscene);
	prep_read(&fd, &buffer, av[1]);
	ret = read(fd, buffer, BUFFER_SIZE);
	while (ret > 0)
	{
		mange_line(buffer, &ret, &backup);
		buffer[ret] = '\0';
		splil_line(buffer, &tscene);
		restor_line(&buffer, &ret, &backup);
		ret = read(fd, buffer + backup, BUFFER_SIZE - backup);
		if (ret == 0)
		{
			buffer[backup + ret] = '\0';
			splil_line(buffer, &tscene);
		}
	}
	copy_tscene(&tscene, scene);
}
