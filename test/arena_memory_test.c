#include "utils.h"

Test(allocate_memory, ft_arena_alloc_test)
{
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_8KB,
        .total_arenas = 0
    };

    int* vector = ft_arena_alloc(3 * sizeof(int), &coliseu);

    ft_memset(vector, 0, 3 * sizeof(int));
    cr_expect(vector[0] == 0, "it is expected that position allocataed to be \\0");
    cr_expect(vector[1] == 0, "it is expected that position allocataed to be \\0");
    cr_expect(vector[2] == 0, "it is expected that position allocataed to be \\0");
    ft_arena_destroy(&coliseu);
}

Test(allocate_with_right_size, ft_arena_alloc_test) {
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_8KB,
        .total_arenas = 0
    };

    char* file_content      = ft_arena_alloc(150, &coliseu);
    ptrdiff_t diff          = coliseu.region->end - coliseu.region->begin;
    ptrdiff_t diff2         = coliseu.region->chunk - sizeof(t_coliseu) - sizeof(void*) - 150;
    cr_expect(coliseu.region->chunk == ARENA_8KB - sizeof(void*), "It is expected do create arena with right size");
    cr_expect(diff2 - diff <= 2, "It is to allocate the correct size");
    ft_arena_destroy(&coliseu);
}

Test(free_arena, ft_arena_alloc_test) {
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_8KB,
        .total_arenas = 0
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
        .size   = ARENA_128B,
        .total_arenas = 0
    };
    
    ft_coliseu_create(&coliseu);
    for (uint8_t i = 1; i < 16; i++) {
        char* space = ft_arena_alloc(1024, &coliseu);
    }
    uint8_t size = 0;
    for (t_arena* aux = coliseu.door; aux != NULL; aux = aux->next) {
     size++;   
    }
    
    cr_expect(size == 16, "expect to free the correct amount of memory and adjust pointer location");
    
    ft_arena_free(&coliseu);
    ft_arena_destroy(&coliseu);
}

Test(arena_allocation, coliseu_rollback) {
    t_coliseu coliseu = {
        .door   = NULL,
        .region = NULL,
        .size   = ARENA_4KB,
        .total_arenas = 0
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
    cr_assert(coliseu.region->begin == mid, "It is expected to return to correct size");
    
    ft_coliseu_rollback(coliseu.region, 1024);
    cr_assert(coliseu.region->begin == ini, "It is expected to return to correct size");

    ft_coliseu_rollback(coliseu.region, 1024);
    cr_assert(coliseu.region->begin == ini, "It is expected to  do nothing when  break arena rollbacl limit");

    ft_arena_destroy(&coliseu);
}


Test(arena_allocator, ft_coliseu_manager) {
    char* ini;
    char* mid;
    char* end;
    
    ini = ft_calloc(1, 1024, NULL);
    mid = ft_calloc(1, 1024, NULL);
    end = ft_calloc(1, 1024, NULL);

    cr_expect(ini != NULL, "expect recieve a valid pointer");
    cr_expect(mid != NULL, "expect recieve a valid pointer");
    cr_expect(end != NULL, "expect recieve a valid pointer");

    ft_coliseu_manager(GIVE_BACK);
}


Test(arena_allocator, resize) {
    t_coliseu coliseu = { .door = NULL, .region = NULL, .size = ARENA_64B, .total_arenas = 0 };


    char* space = ft_arena_alloc(1024, &coliseu);

    ft_strlcpy(space, "JOAO VICTOR", 1024);
    
    int cmp = ft_strncmp(space, "JOAO VICTOR", 11);
    
    cr_expect(cmp == 0, "Espera-se pode escrever");
    
    ft_arena_free(&coliseu);


    space = ft_arena_alloc(1024, &coliseu);
    space = ft_arena_alloc(1024, &coliseu);
    space = ft_arena_alloc(1024, &coliseu);
    space = ft_arena_alloc(1024, &coliseu);
    space = ft_arena_alloc(1024, &coliseu);
    space = ft_arena_alloc(1024, &coliseu);
    space = ft_arena_alloc(1024, &coliseu);
    space = ft_arena_alloc(1024, &coliseu);
    space = ft_arena_alloc(1024, &coliseu);

    cr_expect(space != NULL, "valid addresss");


    ft_arena_destroy(&coliseu);
}

Test(arena_allocator, resize2) {
    t_coliseu coliseu = { .door = NULL, .region = NULL, .size = ARENA_64B, .total_arenas = 0 };

    ft_coliseu_create(&coliseu);

    cr_log_info("avaliabl ANTES: %zu\n", coliseu.region->end - coliseu.region->begin);

    char* space = ft_arena_alloc(32, &coliseu);

    cr_expect(space != NULL, "valid addresss");
    cr_expect(coliseu.total_arenas == 1, "valid addresss");

    space = ft_arena_alloc(1, &coliseu);
    cr_expect(coliseu.total_arenas == 1, "valid addresss");
    cr_log_info("avaliable DEPOIS: %zu\n", coliseu.region->end - coliseu.region->begin);

    space = ft_arena_alloc(1, &coliseu);
    cr_expect(coliseu.total_arenas == 1, "valid addresss");
    cr_log_info("avaliable DEPOIS: %zu\n", coliseu.region->end - coliseu.region->begin);

    space = ft_arena_alloc(1, &coliseu);
    cr_expect(coliseu.total_arenas == 1, "valid addresss");
    cr_log_info("avaliable DEPOIS: %zu\n", coliseu.region->end - coliseu.region->begin);
    
    space = ft_arena_alloc(1024, &coliseu);
    cr_expect(coliseu.total_arenas == 2, "valid addresss");
    cr_log_info("avaliable DEPOIS: %zu\n", coliseu.region->end - coliseu.region->begin);

    ft_arena_destroy(&coliseu);
}