
#include "../../../includes/libft.h"


  void  _vector_insert_at(void* vector, void* item, size_t pos) {
    Vector(void)* v = vector;  

    char* begin = (char*) v->allocator.region->begin;

    v->allocator.region->begin = ((char*) v->allocator.region) + sizeof(t_arena) + pos * v->item_size;

    _vector_push(vector, item);

    v->allocator.region->begin = begin;

    if (pos > v->size) v->size++;

  }
  
  void  _vector_insert_pointer_at(void* vector, void* item, size_t pos) {
    Vector(void)* v = vector;  

    char* begin = (char*) v->allocator.region->begin;

    v->allocator.region->begin = ((char*) v->allocator.region) + sizeof(t_arena) + pos * v->item_size;

    _vector_push_pointer(vector, item);

    v->allocator.region->begin = begin;

  }

  void   _vector_push(void* vector, void* item) {
    Vector(void)* v = vector;  

    if ( !v->items ) {
      printf("ERROR: vector dont initialized\n");
      return ;
    }

    if (v->allocator.region->avaliable <= v->item_size) {
        v->allocator = ft_coliseu_realloc_block(&v->allocator);
        v->items     = ((char*)v->allocator.region) + sizeof(t_arena);
    }

    void* p = ft_calloc(1, v->item_size, &v->allocator);

    ft_memcpy(p, item, v->item_size);

    v->size++;
  }


  void   _vector_push_pointer(void* vector, void* item) {
  Vector(void*)* v = vector;  

    if ( !v->items ) {
      printf("ERROR: vector dont initialized\n");
      return ;
    }

    if ( v->item_size > v->allocator.region->avaliable ) {
      v->allocator = ft_coliseu_realloc_block(&v->allocator);
      v->items     = ((void*)v->allocator.region) + sizeof(t_arena);
    } 

    ft_memcpy((v->items + (v->size * v->item_size)), *(void**)item, v->item_size);
    v->size++;
}

 void*      _vector_pop(void* vector, VectorParams* params) {

    Vector(void)* v = vector;

    ft_coliseu_rollback(v->allocator.region, v->item_size);

    v->size--;

    if (params->buffer) {
      ft_memcpy(params->buffer, v->allocator.region->begin, v->item_size);

      return params->buffer;
    }

    if (params->coliseu) {
      unsigned char* buffer = ft_calloc(1, v->item_size, params->coliseu);

      ft_memcpy(buffer, v->allocator.region->begin, v->item_size);

      return buffer;
    }

    return NULL;
 }

void        _vector_init(void* vector, VectorType type, size_t item_size) {
   Vector(char)* v = vector;

   t_coliseu allocator = { 0 };

   allocator.size = ARENA_2KB;
   allocator.type = ARENA_BLOCK;

   ft_coliseu_create(&allocator);

   v->size       = 0;
   v->items      = allocator.region->begin;
   v->capacity   = ARENA_2KB / item_size;
   v->item_size  = item_size;
   v->allocator  = allocator;
   v->type       = type;
}

void        _vector_destroy(void* vector) {
  Vector(void*)* v = vector;

  ft_arena_destroy(&v->allocator);
}


void  _vector_print(void* vector) {
  Vector(void*)* v = vector;

  if ( v->size < 1 ) {
    printf("[]\n");
    return;
  }

  printf("[");
  size_t index = 0;

  switch(v->type) {
    case TYPE_INT:
      for ( ; index < v->size - 1; index++) {
        printf("%d, ", *(((int*)v->items) + index));
      }
      printf("%d, ", *(((int*)v->items) + index));
    break;
    case TYPE_FLOAT:
      for ( ; index < v->size - 1; index++) {
        printf("%f, ", *(((float*)v->items) + index));
      }
      printf("%f",*(((float*)v->items) + index));
    break;
    case TYPE_CHAR_ARRAY:
      for ( ; index < v->size - 1; index++) {
        printf("%s, ",  (char*)(v->items + (index * sizeof(char*))));
      }
      printf("%s", (char*)(v->items + (index * sizeof(char*))));
    break;
    default:
      printf("NULL");
    break;
  }
  printf("]\n");

}
