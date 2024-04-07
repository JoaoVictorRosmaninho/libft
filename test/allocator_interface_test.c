#include "utils.h"

Test(allocator, monotonic) {
    void* allocated_memory;
    char buffer[8096];
    MonotonicBuffer b = {.buffer = buffer, .offset = 0, .end = 8096};

    Allocator allocator = allocator_new(
        (AllocatorContext) {
            .alloc = ft_monotonic_alloc,
            .free  = NULL,
            .type  = MONOTONIC
        }
    );

    allocated_memory = allocator.alloc(1024, &b);
    cr_assert(allocated_memory != NULL, "expected a valid address");
    
    size_t t  = b.offset;
    size_t t2 = b.end - b.offset;
    
    cr_assert(t  == 1024, "expect to move the offeset to 1024");
    cr_assert(t2 == 7072, "expect to allocate 1024 bytes from local buffer");
}

Test(allocator, coliseu) {
    t_coliseu coliseu = { .door = NULL, .region = NULL, .size = ARENA_2KB };
    void* memory = NULL;
    
    Allocator allocator = allocator_new(
        (AllocatorContext) {
            .alloc   = ft_arena_alloc,
            .free    = ft_arena_free,
            .release = ft_coliseu_release_all,
            .type    = ARENA
        }
    );

    memory = allocator.alloc(1024, &coliseu);
    cr_assert(memory != NULL, "expected a valid address");
    allocator.release(&coliseu, 1);
}

Test(allocator, coliseus) {
    t_coliseu coliseus[3];

    ft_coliseu_initialize(coliseus, 3, ARENA_32KB, ARENA_4KB, ARENA_512B);
    void* memory = NULL;

    Allocator allocator = allocator_new(
        (AllocatorContext) {
            .alloc   = ft_arena_alloc,
            .free    = ft_arena_free,
            .release = ft_coliseu_release_all,
            .type    = ARENA
        }
    );

    memory = allocator.alloc(1024, coliseus);
    memory = allocator.alloc(1024, coliseus + 1);
    memory = allocator.alloc(1024, coliseus + 2);
    cr_assert(memory != NULL, "expected a valid address");
    allocator.release(coliseus, 3);
}