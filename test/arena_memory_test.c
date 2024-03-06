#include "utils.h"

Test(allocate_memory, ft_arena_alloc_test)
{
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_8KB
    };

    int* vector = ft_arena_alloc(3 * sizeof(int), &coliseu);
    cr_expect(vector[0] == 0, "it is expected that position allocataed to be \\0");
    cr_expect(vector[1] == 0, "it is expected that position allocataed to be \\0");
    cr_expect(vector[2] == 0, "it is expected that position allocataed to be \\0");
    ft_arena_destroy(&coliseu);
}

Test(allocate_with_right_size, ft_arena_alloc_test) {
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_8KB
    };

    char* file_content      = ft_arena_alloc(150, &coliseu);
    ptrdiff_t diff          = coliseu.region->end - coliseu.region->begin;
    ptrdiff_t diff2         = coliseu.region->chunk - ARENA_SIZE - ARENA_MALLOC_PTR_SIZE - 150;
    cr_expect(coliseu.region->chunk == ARENA_8KB - ARENA_MALLOC_PTR_SIZE, "It is expected do create arena with right size");
    cr_expect(diff2 - diff <= 2, "It is to allocate the correct size");
    ft_arena_destroy(&coliseu);
}

Test(free_arena, ft_arena_alloc_test) {
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_8KB
    };

    ft_coliseu_create(&coliseu);
    char* start = coliseu.region->begin;

    char* file_content      = ft_arena_alloc(150, &coliseu);

    ft_arena_free(&coliseu);
    cr_expect(start == coliseu.region->begin, "expect to free the correct amount of memory and adjust pointer location");
    ft_arena_destroy(&coliseu);
}

Test(arena_allocation, stress) {
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_128B
    };
    
    ft_coliseu_create(&coliseu);
    for (uint8_t i = 0; i < 16; i++) {
        char* space = ft_arena_alloc(1024, &coliseu);
    }
    uint8_t size = 0;
    for (t_arena* aux = coliseu.door; aux != NULL; aux = aux->next) size++;
    cr_expect(size == 9, "expect to free the correct amount of memory and adjust pointer location");
    
    ft_arena_free(&coliseu);
    ft_arena_destroy(&coliseu);
}

Test(arena_allocation, coliseu_rollback) {
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_4KB
    };
    
    char *ini;
    char *mid;
    char *end;

    ft_coliseu_create(&coliseu);

    ini = coliseu.region->begin;

    ft_arena_alloc(1024, &coliseu);
    mid = coliseu.region->begin;

    ft_arena_alloc(1024, &coliseu);
    end = coliseu.region->begin;

    ft_coliseu_rollback(coliseu.region, 1024);
    cr_expect(coliseu.region->begin == mid, "It is expected to return to correct size");
    
    ft_coliseu_rollback(coliseu.region, 1024);
    cr_expect(coliseu.region->begin == ini, "It is expected to return to correct size");

    ft_coliseu_rollback(coliseu.region, 1024);
    cr_expect(coliseu.region->begin == ini, "It is expected to  do nothing when  break arena rollbacl limit");

    ft_arena_destroy(&coliseu);
}