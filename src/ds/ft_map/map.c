#include "../../../includes/libft.h"

Map*  map_create( size_t size ) {

    Map*       map        = NULL;
    t_coliseu* map_buffer = NULL;

    map_buffer            = ft_coliseu_create_on_arena(ARENA_64B);

    map                   = ft_calloc(1, sizeof(Map), map_buffer);

    map->buffer           = map_buffer;

    map->buckets          = array_list_init_on_buffer( size );

    return map;
}

void  map_delete( Map* map) {
    array_list_deinit(map->buckets);
    
    ft_arena_destroy(map->buffer);
}