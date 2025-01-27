/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:42:47 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/27 11:02:55 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/memory.h"

void	arena_reset(t_arena	*arena)
{
	t_arena_chunk	*chunk;

	if (!arena)
		return ;
	chunk = arena->first;
	while (chunk)
	{
		chunk->used = 0;
		chunk = chunk->next;
	}
	arena->current = arena->first;
	arena->total_used = 0;
}

void	arena_destroy(t_arena	*arena)
{
	t_arena_chunk	*chunk;
	t_arena_chunk	*next;

	if (!arena)
		return ;
	chunk = arena->first;
	while (chunk)
	{
		next = chunk->next;
		arena->free_fn(chunk);
		chunk = next;
	}
	arena->free_fn(arena);
}

size_t	arena_total_used(const t_arena	*arena)
{
	if (arena)
		return (arena->total_used);
	return (0);
}

t_arena_save	arena_save(t_arena	*arena)
{
	t_arena_save	save;

	save.arena = arena;
	save.saved_chunk = arena->current;
	save.saved_used = arena->current->used;
	save.saved_total = arena->total_used;
	return (save);
}

void	arena_restore(t_arena_save save)
{
	t_arena			*arena;
	t_arena_chunk	*chunk;
	t_arena_chunk	*next;

	arena = save.arena;
	if (!arena)
		return ;
	chunk = save.saved_chunk->next;
	while (chunk)
	{
		next = chunk->next;
		arena->free_fn(chunk);
		chunk = next;
	}	
	save.saved_chunk->next = NULL;
	save.saved_chunk->used = save.saved_used;
	arena->current = save.saved_chunk;
	arena->total_used = save.saved_total;
}
