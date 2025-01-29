/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:47 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/01/28 22:24:47 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/memory.h"

t_arena	**get_arena(void)
{
	static t_arena	*arena = NULL;

	return (&arena);
}

void	set_arena(t_arena *new_arena)
{
	t_arena	**arena;

	arena = get_arena();
	*arena = new_arena;
}

void	setup_arena(void)
{
	t_arena	*arena;

	arena = arena_create();
	set_arena(arena);
}
