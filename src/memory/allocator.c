#include "libft.h"

Allocator allocator_new(AllocatorContext context) {
    return (Allocator) {
        .alloc   = context.alloc,
        .free    = context.free,
        .release = context.release
    };
}