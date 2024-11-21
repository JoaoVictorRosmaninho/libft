#ifndef FT_MAP_H
#define FT_MAP_H

#include "linked.h"
#include "arena.h"

typedef struct s_map_pair{
   ArrayList*         link;
   const void*        key;
   void*              value;
} MapPair;

typedef struct {
   ArrayList*  buckets;
   t_coliseu*  buffer;
} Map;


Map*  map_create( size_t size );

void  map_delete( Map* map);


#endif