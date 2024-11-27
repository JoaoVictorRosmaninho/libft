#include "../../../includes/libft.h"


static size_t map_hash(Data* pair) {    

    (void) pair;
    return 0;
}

static uint8_t  map_equal(Data* a, Data* b) {
    return a == b;
}


Map*  map_create(uint8_t (*cmp)(Data*, Data*), size_t (*hashf)(Data*) ) {

    Map*       map        = NULL;
    t_coliseu* map_buffer = NULL;

    map_buffer            = ft_coliseu_create_on_arena(ARENA_128B, ARENA_BLOCK);

    map                   = ft_calloc(1, sizeof(Map), map_buffer);

    map->buffer           = map_buffer;

    map->buckets          = array_list_init_on_buffer();

    map->capacity         = ft_coliseu_size(map->buckets->bucket) / sizeof(Data);

    map->cmp              = cmp != NULL ? cmp : map_equal;

    map->hashf            = hashf != NULL ? hashf : map_hash;

    map->insert           = map_insert;

    return map;
}

static inline ArrayList*  map_neasted_bucket(Map* map, size_t index) {
    return map->buckets->array[index].content.p;
}

static void map_insert_or_update_bucket(Map* map, Data* pair, size_t index) {
    ArrayList* bucket = map_neasted_bucket(map, index);

    for (size_t i = 0; i < bucket->index; i++) {
        if (map->cmp(bucket->array + i, pair)) {
            array_list_add_data_on(bucket, i, pair);
            return ;
        }
    }

    array_list_add_data(bucket, pair);
}

Map*     map_insert( Map* map, Data* pair ) {
    size_t hash_value = map->hashf(pair) % map->capacity;

    if (map->buckets->array[hash_value].content.p) { // conflict
        map_insert_or_update_bucket(map, pair, hash_value);

        return map;
    }


    // Criando data para armazenar o pointer do arrayList
    Data* data      = ft_calloc(1, sizeof(Data), map->buffer);
 
    // criando arrayList para armazenar colisions
    data->content.p = array_list_init_on_buffer();

    // adicionando primeiro item no array de items
    array_list_add_data(data->content.p, pair);

    // adicionando array criado no respectivo hash_value
    array_list_add_data_on(map->buckets, hash_value, data);

   // if ( ((float)map->buckets->index / map->capacity) > 0.6 ) {
   //     size_t adrss    = (char*)map->buckets - (char*)map->buckets->bucket->region;  
   //     t_coliseu* tmp   = ft_coliseu_realloc_block(map->buckets->bucket);
//
   //     map->buckets          = (ArrayList*) (map->buckets->bucket + adrss);
   //     map->buckets->bucket  = tmp;
   //     map->capacity         = ft_coliseu_size(map->buckets->bucket) / sizeof(Data);
   // }

    return map;
}

void  map_destroy( Map* map) {

    for (size_t i = 0; i < map->capacity; i++) {
        if (!map->buckets->array[i].content.p) continue;

        array_list_deinit(map->buckets->array[i].content.p);
    }
    array_list_deinit(map->buckets);
    ft_arena_destroy(map->buffer);
}

Data*    map_get(Map* map, Data* pair) {
    size_t hash_value = map->hashf(pair) % map->capacity;

    ArrayList* bucket = map_neasted_bucket(map, hash_value);
    
    if ( !bucket ) return NULL;

    for (size_t i = 0; i < bucket->index; i++) {
        if (map->cmp(bucket->array + i, pair)) {
            return bucket->array + i;
        }
    }

    return NULL;
}