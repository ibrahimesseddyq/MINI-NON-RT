/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:23:53 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/01/28 22:23:53 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

char	get_ascii(int key)
{
	if (key == KEY_1)
		return ('1');
	else if (key == KEY_2)
		return ('2');
	else if (key == KEY_3)
		return ('3');
	else if (key == KEY_4)
		return ('4');
	else if (key == KEY_5)
		return ('5');
	else if (key == KEY_6)
		return ('6');
	else if (key == KEY_7)
		return ('7');
	else if (key == KEY_8)
		return ('8');
	else if (key == KEY_9)
		return ('9');
	else
		return ('\0');
}

int	my_atoi(int *keys, int start)
{
	int		i;
	char	array[9];
	int		array_index;
	char	ascii;

	memset(array, 0, 9);
	array_index = 0;
	i = start;
	while (i < 8)
	{
		ascii = get_ascii(keys[i]);
		if (ascii == '\0')
			break ;
		array[array_index++] = ascii;
		i++;
	}
	array[array_index] = '\0';
	return (ft_atoi(array));
}
