#include "libft.h"

Allocator allocator_new(AllocatorContext context) {
    return (Allocator) {
        .alloc   = context.alloc,
        .free    = context.free,
        .release = context.release
    };
}


Allocator allocator_for_arena(void) {
    return (Allocator) {
        .alloc   = ft_arena_alloc,
        .free    = ft_arena_free,
        .release = ft_coliseu_release_all 
    };
}

Allocator allocator_for_monotonic(void) {
    return (Allocator){
        .alloc   = ft_monotonic_alloc,
        .free    = NULL,
        .release = NULL
    };
}