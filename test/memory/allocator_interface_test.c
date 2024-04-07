#include "../utils.h"

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

    ft_coliseu_initialize(coliseus, 3, ARENA_32KB);
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


Test(allocator, temp_arena) {
    t_coliseu coliseu   = { .door = NULL, .region = NULL, .size = ARENA_512B };
    Allocator allocator = allocator_for_arena();

    void* memory;

    // then

    memory      = allocator.alloc(64, &coliseu);
    char* begin = coliseu.region->begin;

    cr_assert(memory != NULL, "expect a valid memory pointer");

    TmpArena tmp = tmp_coliseu_new(&coliseu);

    memory       = allocator.alloc(64, tmp.coliseu);

    cr_assert(memory != NULL, "expect a valid memory pointer");
    cr_assert( begin < coliseu.region->begin, "expect to move the pointer foward");

    tmp_coliseu_end(&tmp);

    cr_assert(begin == coliseu.region->begin, "expect to return the pointer for the initial");


    allocator.release(&coliseu, 1); 
}

Test(allocator, temp_arena_with_global_coliseu) {
    Allocator allocator = allocator_for_arena();
    void*     memory    = NULL;
    TmpArena  tmp       = tmp_coliseu_new(ft_coliseu_manager(TAKE));

    char*     begin     = tmp.coliseu->region->begin;

    memory              = allocator.alloc(1024, tmp.coliseu);

    cr_expect( memory != NULL, "expect to return a valid address");

    cr_assert( begin < tmp.coliseu->region->begin, "expect to move the pointer foward");
    tmp_coliseu_end(&tmp);

    cr_expect( begin == tmp.coliseu->region->begin, "expect to return the pointer to real begin address");

    ft_coliseu_manager(FREE);
}
