/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_obj_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:26:51 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/15 19:10:53 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

int	count_args(const char **inf)
{
	int	arg_count;

	arg_count = 0;
	while (inf[arg_count] != NULL)
		arg_count++;
	printf("arg_count: %d\n", arg_count);
	return (arg_count);
}

int	parse_material(const char *mat, t_material *material)
{
	char	**tab;

	printf("mat: %s\n", mat);
	if (check_pnt(mat) != 3)
		return (false);
	tab = ft_split(mat, ',');
	if (count_args((const char **)tab) != 4)
		clean_exit("Error: Material has wrong number of arguments");
	material->ka = ft_atof(tab[0]);
	material->kd = ft_atof(tab[1]);
	material->ks = ft_atof(tab[2]);
	material->n = ft_atoi(tab[3]);
	if (material->ka > 1 || material->kd > 1 || material->ks > 1
		|| material->n < 0 || material->ka < 0 || material->kd < 0
		|| material->ks < 0)
		clean_exit("Error: Material has wrong arguments");
	printf("end`);");
	return (true);
}
