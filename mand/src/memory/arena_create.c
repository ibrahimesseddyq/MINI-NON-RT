/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:39:57 by sessarhi          #+#    #+#             */
/*   Updated: 2025/02/15 12:10:39 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/memory.h"

t_arena	*arena_create(void)
{
	return (arena_create_with_params(DEFAULT_CHUNK_SIZE, true, malloc, free));
}

t_arena	*arena_create_with_params(size_t chunk_size, bool allow_resize,
			void *(*alloc_fn)(size_t), void (*free_fn)(void*))
{
	t_arena			*arena;
	t_arena_chunk	*chunk;

	if (chunk_size < MIN_CHUNK_SIZE)
		chunk_size = MIN_CHUNK_SIZE;
	chunk_size = align_up(chunk_size, ARENA_ALIGNMENT);
	if (!alloc_fn)
		alloc_fn = malloc;
	if (!free_fn)
		free_fn = free;
	arena = (t_arena *)alloc_fn(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->chunk_size = chunk_size;
	arena->allow_resize = allow_resize;
	arena->total_allocated = 0;
	arena->total_used = 0;
	arena->alloc_fn = alloc_fn;
	arena->free_fn = free_fn;
	chunk = arena_allocate_chunk(arena, chunk_size);
	if (!chunk)
		return (free_fn(arena), NULL);
	arena->first = chunk;
	arena->current = chunk;
	return (arena);
}

size_t	arena_total_allocated(const t_arena	*arena)
{
	if (arena)
		return (arena->total_allocated);
	return (0);
}
