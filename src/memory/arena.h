#ifndef ARENA_H
# define ARENA_H

# include <stdint.h>
# include "../../includes/libft.h"

# define ARENA_MIN_ALLOC_SIZE 8
# define ARENA_MALLOC_PTR_SIZE sizeof(void*)
# define ARENA_ALIGN_SIZE 16
# define ARENA_SIZE sizeof(t_arena)

# define ARENA_64B 64 // 64 bytes
# define ARENA_128B 128 // 128 bytes
# define ARENA_256B 256 // 256 bytes
# define ARENA_512B 512 // 512 bytes
# define ARENA_1M 1024 // 1kb
# define ARENA_2M 2056 // 2kb
# define ARENA_4M 4096 //  4kb
# define ARENA_8M 8192 // 8kb
# define ARENA_16M 16384 // 16KB
# define ARENA_32M 32768 // 32KB
# define ARENA_65M 65536 // 65KB
# define ARENA_131M 131072 // 130KB


// T h e arenas for objects with lifetime t are linked together

typedef long ptrdiff_t;

typedef struct s_arena{
    struct s_arena* next; // link to next arena
    size_t chunk;     // size allocated for this arena
    char* end;          // endereço de um final da arena
    char* begin;      // next begin location
} t_arena;

typedef struct {
    t_arena *door;
    t_arena *region;
    size_t  size;
} t_coliseu;


// Arena Interface:

// free arena:
void ft_arena_free(t_coliseu *coliseu);
// destroy_arena and free process memory
void ft_arena_destroy(t_coliseu *coliseu);
// alloc memory from specific arena
void* ft_arena_alloc(size_t chunk, t_coliseu *coliseu);
// create a coliseu
void ft_coliseu_create(t_coliseu* coliseu);

#endif