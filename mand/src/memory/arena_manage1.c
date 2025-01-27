/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_mange1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:02:35 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/27 11:03:31 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/memory.h"

t_arena	**get_arena(void)
{
	static t_arena	*arena;

	return (&arena);
}

void	set_arena(t_arena	*new_arena)
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
