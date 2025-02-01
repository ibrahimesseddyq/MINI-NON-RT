/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:23:40 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/23 11:40:04 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt_bonus.h"

void	clean_exit(const char *msg)
{
	int	fds;

	fds = 10;
	arena_destroy(*get_arena());
	while (--fds > 2)
		close(fds);
	printf("%s\n", msg);
	exit(1);
}
