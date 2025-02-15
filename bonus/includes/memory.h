/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:40:25 by ibes-sed          #+#    #+#             */
/*   Updated: 2025/02/15 14:06:44 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H
# include "includes.h"
# include "../../minirt_bonus.h"
# define ARENA_ALIGNMENT 8
# define DEFAULT_CHUNK_SIZE 104857600
# define MIN_CHUNK_SIZE 4096

typedef struct s_arena_chunk
{
	struct s_arena_chunk	*next;
	size_t					size;
	size_t					used;
	uintptr_t				data[];
}	t_arena_chunk;

typedef struct s_arena
{
	t_arena_chunk	*current;
	t_arena_chunk	*first;
	size_t			chunk_size;
	size_t			total_allocated;
	size_t			total_used;
	bool			allow_resize;
	void			*(*alloc_fn)(size_t);
	void			(*free_fn)(void*);
}	t_arena;

typedef struct s_arena_save
{
	t_arena			*arena;
	t_arena_chunk	*saved_chunk;
	size_t			saved_used;
	size_t			saved_total;
}	t_arena_save;

t_arena_chunk	*arena_allocate_chunk(t_arena *arena, size_t min_size);
void			*arena_alloc_from_chunk(t_arena_chunk *chunk,
					size_t size, size_t align);
t_arena			*arena_create(void);
t_arena			*arena_create_with_params(size_t chunk_size, bool allow_resize,
					void *(*alloc_fn)(size_t), void (*free_fn)(void*));
t_arena_chunk	*arena_allocate_chunk(t_arena *arena, size_t min_size);
void			*arena_aligned_alloc(t_arena *arena, size_t size, size_t align);
void			*arena_alloc(t_arena *arena, size_t size);
void			*arena_alloc_from_chunk(t_arena_chunk *chunk,
					size_t size, size_t align);
void			arena_reset(t_arena *arena);
void			arena_destroy(t_arena *arena);
size_t			arena_total_allocated(const t_arena *arena);
size_t			arena_total_used(const t_arena *arena);
t_arena_save	arena_save(t_arena *arena);
void			arena_restore(t_arena_save save);
void			arena_restore(t_arena_save save);
t_arena			**get_arena(void);
void			setup_arena2(t_arena *arena,
					bool allow_resize, void *(*alloc_fn)(size_t),
					void (*free_fn)(void *));
size_t			align_up(size_t n, size_t align);
#endif