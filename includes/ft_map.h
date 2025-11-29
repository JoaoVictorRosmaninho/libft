#ifndef FT_MAP_H
#define FT_MAP_H

#include <stdint.h>
#include <stdlib.h>

# include <stdint.h>
# include "arena.h"
# include "linked.h"
# include "vector.h"

typedef struct t_map {
   void**         buckets; // -> irar armazenar ponteiros para outros arrayLists
   t_coliseu*     buffer;
   size_t         capacity;
   uint8_t        (*cmp)(Data*, Data*);
   uint64_t       (*hashf)(Data*);
   struct t_map*  (*insert)(struct t_map*, Data*);
} Map;

#define hashmap(key_type, value_type)         

Map*     map_create(uint8_t (*cmp)(Data*, Data*), uint64_t (*hashf)(Data*) );

void     map_destroy( Map* map );

Map*     map_insert( Map* map, Data* pair );

Data*    map_get(Map* map, Data* pair); 

// hash functions

size_t hashs(Data* pair);

size_t hashi(Data* pair);

size_t hashui(Data* pair);

size_t hashf(Data* pair);

size_t hashd(Data* pair);


#endif