#ifndef FT_MAP_H
#define FT_MAP_H


typedef struct {
   struct binding {
      struct binding* link;
      const void*     key;
      void*           value;
   } **buckets;
} Map;


#endif