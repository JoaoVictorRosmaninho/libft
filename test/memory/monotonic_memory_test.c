#include "../utils.h"

Test(monotonic, monotonic_alloc) {

    char  space[2048];
    void* allocated_memory  = NULL;

    MonotonicBuffer  buffer = ft_monotonic_buffer_new(2048, space);
    allocated_memory        = ft_monotonic_alloc(1024, &buffer);

    cr_assert(allocated_memory != NULL, "expected a valid address");
    cr_assert(buffer.offset    == 1024, "expecto to move the offeset to 1024");
    cr_assert(buffer.end - buffer.offset == 1024, "expect to allocate 1024 bytes from local buffer");
    cr_assert(buffer.coliseu_used == 0, "expect to not use arena for allocate the memory");
}

Test(monotonic, monotonic_alloc_null_pointer) {

    char  space[2048];
    void* allocated_memory  = NULL;

    MonotonicBuffer  buffer = ft_monotonic_buffer_new(2048, space);
    allocated_memory        = ft_monotonic_alloc(4092, &buffer);

    cr_assert(allocated_memory == NULL, "expected to return null pointer");
}

/* Problemarico  usando  arenas*/
/*
Test(monotonic, monotonic_alloc_using_arena) {

    char  space[2048];
    void* allocated_memory  = NULL;

    MonotonicBuffer  buffer = ft_monotonic_buffer_new(2048, space);
    allocated_memory        = ft_monotonic_alloc(1024, &buffer);

    cr_assert(allocated_memory != NULL, "expected a valid address");
    cr_assert(buffer.offset    == 1024, "expecto to move the offeset to 1024");
    cr_assert(buffer.end - buffer.offset == 1024, "expect to allocate 1024 bytes from local buffer");
    cr_assert(buffer.coliseu_used == 0, "expect to not use arena for allocate the memory");

    allocated_memory            = ft_monotonic_alloc(2048, &buffer);
    cr_assert(allocated_memory != NULL, "expected a valid address");
    cr_assert(buffer.coliseu_used == 1, "expect to not use arena for allocate the memory");
    ft_arena_destroy(&buffer.coliseu);
}
*/