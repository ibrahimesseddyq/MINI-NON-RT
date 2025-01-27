/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:09:07 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/25 22:39:18 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

int	process_co(char **inf, t_tscene *t_scene);

void	splil_line(const char *line, t_tscene *tscene)
{
	char	**elm;
	char	**inf;
	int		i;

	i = 0;
	elm = ft_split(line, '\n');
	while (elm[i])
	{
		inf = ft_split(elm[i], ' ');
		printf("elm [%s]\n", elm[i]);
		printf("[%s]\n", inf[0]);
		if (ft_strcmp(inf[0], "A") == 0 && !process_a(inf, tscene))
			i++;
		else if (ft_strcmp(inf[0], "C") == 0 && !process_c(inf, tscene))
			i++;
		else if (ft_strcmp(inf[0], "L") == 0 && !process_l(inf, tscene))
			i++;
		else if (ft_strcmp(inf[0], "sp") == 0 && !process_sp(inf, tscene))
			i++;
		else if (ft_strcmp(inf[0], "pl") == 0 && !process_pl(inf, tscene))
			i++;
		else if (ft_strcmp(inf[0], "cy") == 0 && !process_cy(inf, tscene))
			i++;
		else if (ft_strcmp(inf[0], "co") == 0 && !process_co(inf, tscene))
			i++;
		else
			return (printf("Error \n"), exit(1));
	}
}

void	restor_line(char **buffer, int *ret, int *backup)
{
	int		i;
	char	*buf;

	buf = *buffer;
	*ret += 1;
	i = 0;
	while (buf[*ret] != '\0')
	{
		buf[i] = buf[*ret];
		i++;
		(*ret)++;
	}
	*backup = i;
}

void	int_tsceen(t_tscene *tscene)
{
	tscene->cylinder = NULL;
	tscene->plane = NULL;
	tscene->sphere = NULL;
	tscene->light = NULL;
	tscene->plane_size = 0;
	tscene->cylinder_size = 0;
	tscene->sphere_size = 0;
	tscene->light_size = 0;
	tscene->is_c_set = false;
	tscene->is_l_set = false;
	tscene->is_a_set = false;
	tscene->camera.position.x = 0;
	tscene->camera.position.y = 0;
	tscene->camera.position.z = 0;
	tscene->camera.direction.x = 0;
	tscene->camera.direction.y = 0;
	tscene->camera.direction.z = 0;
}

bool	mange_line(char *buffer, int *ret, int *backup)
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
