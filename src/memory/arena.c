#include "arena.h"

static size_t ft_align(size_t request_size) {
    return (((request_size) + ((ARENA_ALIGN_SIZE) - 1)) & ~((ARENA_ALIGN_SIZE) - 1));
}

static t_arena* ft_arena_init(size_t chunk) // 1024 bytes min (4096)
{
    t_arena* arena;

    if (chunk & (chunk -1))
    {
        ft_printf("Tamanho precisa ser uma potência de 2, ex: 4096");
        return (NULL);
    }

    if (chunk < ARENA_MALLOC_PTR_SIZE || (chunk - ARENA_MALLOC_PTR_SIZE) < ARENA_ALIGN_SIZE) {
        ft_printf("tamanho %d menor que o minimo aceitável\n", chunk);
        return (NULL);
    }
    chunk -= ARENA_MALLOC_PTR_SIZE;
    
    if (chunk <= ARENA_SIZE ) {
        // Se o tamanho restante for inferior ao tamanho da arena: error
        ft_printf("Tamanho restante %d é inferior ao tamanho minimo da arena\n", chunk);
        return (NULL);
    }

    arena = (t_arena*) ft_calloc(1, chunk); // Alocando o chunk
    if (!arena) {
        ft_printf("Tamanho, insuficiente para Arena\n");
        return (NULL);
    }
    arena->chunk  = chunk;
    arena->begin = (char*) arena + ARENA_SIZE; 
    arena->end   = (char*) arena + chunk;
    arena->next  = NULL;
    return (arena);
}


void ft_coliseu_create(t_coliseu* coliseu) {
    coliseu->door = ft_arena_init(coliseu->size);
    if (!coliseu->door) {
        ft_printf("Não foi possivel alocar o espaço %d para a arena\n", coliseu->size);
        return;
    }
    coliseu->region = coliseu->door;
}


static void* ft_find_or_create_arena(t_coliseu *coliseu, size_t chunk) {
    
    t_arena* _arena;
    ptrdiff_t avaliable;
    ptrdiff_t real_size;

    _arena = coliseu->region;
    while(1) {
        avaliable = _arena->end - _arena->begin;
        if ((ptrdiff_t) chunk > avaliable) {
            if (_arena->next) {
                // O ideal é sempre procurar espaço na arena disponivel, mas como é uma linked list, é demorado
                _arena = _arena->next; // possivel "leak"
                continue;
            } else {
                if (chunk > (PTRDIFF_MAX - ARENA_SIZE)) {
                    ft_printf("Erro: requisição de memoria muito grande\n");
                    return (NULL);
                }
                if (coliseu->region && coliseu->size)
                    real_size = coliseu->region->chunk;
                else
                    real_size = coliseu->size;
                while ((ptrdiff_t)(chunk + ARENA_SIZE) > real_size)
                    real_size *= 2;
                coliseu->region = coliseu->region->next = ft_arena_init(real_size);
            }
        }
        break;
    }
    return (coliseu->region->begin);
}

void    ft_arena_free(t_coliseu *coliseu)
{
    t_arena *arena;

    arena = coliseu->door;
    if (!arena) {
        ft_printf("endereço de arena inválido\n");
        return ;
    }
    while (arena) {
        arena->begin = (char*) arena + ARENA_SIZE;
        arena = arena->next;
    }
}

void ft_arena_destroy(t_coliseu *coliseu)
{
    t_arena* arena;
    t_arena* _arena;

    arena = coliseu->door;
    while(arena) {
        _arena = arena;
        arena = arena->next;
        free(_arena);
    }
    coliseu->door   = NULL;
    coliseu->region = NULL;
}

void* ft_arena_alloc(size_t chunk, t_coliseu *coliseu) {
    
    void* memory;
    ptrdiff_t real_chunk;

    if (!coliseu || !chunk)
    {
        ft_printf("Coliseu inválido ou tamanho invalido\n");
        return (NULL);
    }
    real_chunk = ft_align(chunk);
    if (!coliseu->region)
    {
        if (!coliseu->size)  {
            ft_printf("Coliseu inválido\n");
            return (NULL);
        }
        ft_coliseu_create(coliseu);
        memory = ft_find_or_create_arena(coliseu, chunk);
    } else {
        memory = coliseu->region->begin;
        if ((real_chunk + ARENA_SIZE) > PTRDIFF_MAX) {
           // ft_printf("Impossivel  alocar, overflow condition\n");
            return (NULL);
        }
        // Marcando como usada
        if (coliseu->region->begin > coliseu->region->end) {
            // Não tem meomoria suficiente
            // alocar uma nova
            memory = ft_find_or_create_arena(coliseu, chunk);
        }
    }
    coliseu->region->begin += real_chunk;
    return (memory);
}