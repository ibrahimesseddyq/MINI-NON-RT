/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:09:07 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/13 13:31:19 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

int	process_co(char **inf, t_tscene *t_scene);

static void	parse_object(char	**inf, t_tscene *tscene)
{
	if (ft_strcmp(inf[0], "A") == 0 && !process_a(inf, tscene))
		;
	else if (ft_strcmp(inf[0], "C") == 0 && !process_c(inf, tscene))
		;
	else if (ft_strcmp(inf[0], "L") == 0 && !process_l(inf, tscene))
		;
	else if (ft_strcmp(inf[0], "sp") == 0 && !process_sp(inf, tscene))
		;
	else if (ft_strcmp(inf[0], "pl") == 0 && !process_pl(inf, tscene))
		;
	else if (ft_strcmp(inf[0], "cy") == 0 && !process_cy(inf, tscene))
		;
	else if (ft_strcmp(inf[0], "co") == 0 && !process_co(inf, tscene))
		;
	else
		return (printf("Error \n"), clean_exit(""));
}

void	splil_line(char *line, t_tscene *tscene)
{
	char	**elm;
	char	**inf;
	int		i;

	i = 0;
	elm = ft_split(line, '\n');
	while (elm[i])
	{
		inf = ft_split(elm[i], ' ');
		parse_object(inf, tscene);
		i++;
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
	tscene->cone = NULL;
	tscene->light = NULL;
	tscene->plane_size = 0;
	tscene->cylinder_size = 0;
	tscene->sphere_size = 0;
	tscene->light_size = 0;
	tscene->cone_size = 0;
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
