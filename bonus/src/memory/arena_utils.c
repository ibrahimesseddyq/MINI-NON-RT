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
