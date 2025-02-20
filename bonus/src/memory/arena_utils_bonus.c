/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:24:47 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/20 10:11:44 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/memory_bonus.h"

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
