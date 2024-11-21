#ifndef FT_MAP_H
#define FT_MAP_H

#define T Map;

typedef struct {
   uint16_t     hint;      
   t_coliseu*   buffer;
   uint16_t     (*hash)(void*, void*);
   uint8_t      (*cmp)(void*, void*);
} T;


#endif