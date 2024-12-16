#include "../../includes/memory.h"

t_arena_chunk* arena_allocate_chunk(t_arena* arena, size_t min_size)
{
    size_t chunk_size;
    t_arena_chunk* chunk;

    chunk_size = arena->chunk_size;
    if (min_size > chunk_size - sizeof(t_arena_chunk))
    {
        chunk_size = min_size + sizeof(t_arena_chunk);
        chunk_size = ALIGN_UP(chunk_size, ARENA_ALIGNMENT);
    }
    chunk = (t_arena_chunk*)arena->alloc_fn(chunk_size);
    if (!chunk)
        return (NULL);
    chunk->next = NULL;
    chunk->size = chunk_size;
    chunk->used = 0;
    arena->total_allocated += chunk_size;
    return (chunk);
}

void* arena_aligned_alloc(t_arena* arena, size_t size, size_t align)
{
    void* ptr;
    t_arena_chunk* new_chunk;

    if (size == 0)
        return (NULL);
    if (align < ARENA_ALIGNMENT) align = ARENA_ALIGNMENT;
    ptr = arena_alloc_from_chunk(arena->current, size, align);
    if (ptr)
        return (arena->total_used += size, ptr);
    if (!arena->allow_resize)
        return (NULL);
    new_chunk = arena_allocate_chunk(arena, size + align);
    if (!new_chunk)
        return (NULL);    
    new_chunk->next = arena->current->next;
    arena->current->next = new_chunk;
    arena->current = new_chunk;    
    ptr = arena_alloc_from_chunk(new_chunk, size, align);
    if (ptr)
        arena->total_used += size;
    return (ptr);
}

void* arena_alloc(t_arena* arena, size_t size)
{
    return (arena_aligned_alloc(arena, size, ARENA_ALIGNMENT));
}

void* arena_alloc_from_chunk(t_arena_chunk* chunk, size_t size, size_t align)
{
    uintptr_t current;
    uintptr_t aligned ;
    size_t padding;
    size_t total_size;

    current = (uintptr_t)&chunk->data[chunk->used];
    aligned = ALIGN_UP(current, align);
    padding = aligned - current;
    total_size = padding + size;
    if (chunk->used + total_size > chunk->size - sizeof(t_arena_chunk))
        return (NULL);
    chunk->used += total_size;
    return ((void*)aligned);
}

size_t arena_total_allocated(const t_arena* arena)
{
    if (arena)
        return (arena->total_allocated);
    return (0);
}