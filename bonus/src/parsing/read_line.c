/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:38:19 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/26 11:17:42 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	int_tsceen(t_tscene *tscene);
bool	mange_line(char *buffer, int *ret, int *backup);
void	restor_line(char **buffer, int *ret, int *backup);

static void	ft_handle_buffer(char *buffer, int ret,
			int backup, t_tscene *tscene)
{
	buffer[ret] = '\0';
	splil_line(buffer, tscene);
	restor_line(&buffer, &ret, &backup);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

static void	ft_read_file(int fd, char *buffer, t_tscene *tscene)
{
	int	ret;
	int	backup;

	ret = read(fd, buffer, BUFFER_SIZE);
	while (ret > 0)
	{
		if (!mange_line(buffer, &ret, &backup))
		{
			write(2, "error file empty or line too long\n", 35);
			exit(1);
		}
		ft_handle_buffer(buffer, ret, backup, tscene);
		ret = read(fd, buffer + backup, BUFFER_SIZE - backup);
		if (ret == 0)
		{
			buffer[backup + ret] = '\0';
			splil_line(buffer, tscene);
		}
	}
}

void	process_flie(char **av, t_scene *scene)
{
	int			fd;
	char		*buffer;
	t_tscene	tscene;

	int_tsceen(&tscene);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error can't open ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	buffer = malloc(BUFFER_SIZE);
	ft_read_file(fd, buffer, &tscene);
	copy_tscene(&tscene, scene);
	close(fd);
	free(buffer);
}
