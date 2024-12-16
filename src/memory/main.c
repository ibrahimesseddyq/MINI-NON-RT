#include "../../includes/memory.h"



// int main() {
//     // Create arena with 64KB chunks
//     t_arena* arena = arena_create_with_params(64 * 1024, true, malloc, free);
    
//     // Basic allocation
//     int* numbers = arena_alloc(arena, 10 * sizeof(int));
//     for (int i = 0; i < 10; i++) {
//         numbers[i] = i;
//     }
    
//     // Aligned allocation
//     float* vectors = arena_aligned_alloc(arena, 16 * sizeof(float), 16);
    
//     // Temporary scope
//     t_arena_save save = arena_save(arena);
//     void* temp = arena_alloc(arena, 1024);
//     // ... use temporary allocation ...
//     arena_restore(save);  // Roll back temporary allocation
    
//     // Print stats
//     printf("Total allocated: %zu bytes\n", arena_total_allocated(arena));
//     printf("Total used: %zu bytes\n", arena_total_used(arena));
    
//     // Clean up
//     arena_destroy(arena);
//     return 0;
// }
