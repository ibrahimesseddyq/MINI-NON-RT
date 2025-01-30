/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:38:19 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/29 22:49:44 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	int_tsceen(t_tscene *tscene);
bool	mange_line(char *buffer, int *ret, int *backup);
void	restor_line(char **buffer, int *ret, int *backup);

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
typedef struct s_process_file
{
	int fd;
	int ret;
	char *buffer;
	int backup;
	t_tscene tscene;
} t_process_file;
void	process_flie(char **av, t_scene *scene)
{
	t_process_file	pi;

	int_tsceen(&pi.tscene);
	pi.fd = open(av[1], O_RDONLY);
	if (pi.fd == -1)
		return (printf("Error can't open %s\n", *av), exit(1));
	pi.buffer = malloc(BUFFER_SIZE);
	pi.ret
		= read(pi.fd, pi.buffer, BUFFER_SIZE);
	while (pi.ret > 0)
	{
		if (!mange_line(pi.buffer, &pi.ret, &pi.backup))
			return (printf("error file empty or line too long\n"), exit(1));
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
	copy_tscene(&pi.tscene, scene);
	close(pi.fd);
}
