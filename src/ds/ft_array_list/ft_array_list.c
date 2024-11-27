
#include "../../../includes/libft.h"


void array_list_print(ArrayList* arraylist) {
  ft_printf("[");
  for( size_t i = 0; i < arraylist->index; i++) {
    switch (arraylist->array[i].content_type) 
    {
      case STRING:
        ft_printf("%s", arraylist->array[i].content.s);
      break;
      case INTEGER:
        ft_printf("%d", arraylist->array[i].content.i);
      break;
      case FLOAT:
        ft_printf("%f", arraylist->array[i].content.f);
      break;
      case DOUBLE:
        ft_printf("%f", arraylist->array[i].content.d);
      break;
      case CHAR:
        ft_printf("%c", arraylist->array[i].content.c);
      break;
      default:
        ft_printf("%p", arraylist->array[i].content.p);
      break;
    }
    if ( i < arraylist->index - 1 ) ft_printf(", ");
  }
  ft_printf("]\n");
}



ArrayList   array_list_init() {
    t_coliseu* coliseu_array = ft_coliseu_create_on_arena( ARENA_131KB, ARENA_BLOCK );

    ArrayList array =  {
        .bucket =  coliseu_array,
        .array        =  (Data*)coliseu_array->region->begin,
        .index        =  0
    };

    return array;
}

ArrayList*   array_list_init_on_buffer( void ) {
    t_coliseu* bucket = ft_coliseu_create_on_arena( ARENA_32KB , ARENA_BLOCK );

    ft_memset(bucket->region->begin, 0, bucket->region->end - bucket->region->begin);

    ArrayList* array  = ft_calloc(1, sizeof(ArrayList), bucket);

    array->bucket     = bucket;
    array->array      = (Data*) bucket->region->begin;
    array->index      = 0;

    return array;
}

void   array_list_deinit( ArrayList* array ) {
    ft_arena_destroy(array->bucket);
}

ArrayList*  array_list_add_int(ArrayList* array, int n) {
  mk_int_content(n, array->bucket);
  
  array->index++;
  return array;
}

ArrayList*  array_list_add_str(ArrayList* array, char* string) {
  mk_string_content(string, array->bucket);
  array->index++;
  return array;
}

ArrayList*  array_list_pop( ArrayList* array ) {
     array->index--;
     ft_coliseu_rollback(array->bucket->region, sizeof(Data));
     return array;
}

ArrayList*  array_list_add_float(ArrayList* array, float n) {
  mk_float_content(n, array->bucket);
  array->index++;
  return array;
}

ArrayList*  array_list_add_double(ArrayList* array, double n) {
  mk_double_content(n, array->bucket);
  array->index++;
  return array;
}

ArrayList*  array_list_add_data(ArrayList* array, Data* n) {
  mk_data_content(n, array->bucket);
  array->index++;
  return array;
}

ArrayList*  array_list_add_str_on(ArrayList* array, size_t index, char* n) {

  char* begin                  = array->bucket->region->begin;

  array->bucket->region->begin = (char*) (array->array + index);

  mk_string_content(n, array->bucket);

  array->bucket->region->begin = begin;

  return array;  
}

ArrayList*  array_list_add_data_on(ArrayList* array, size_t index, Data* n) {
  char* begin                  = array->bucket->region->begin;

  array->bucket->region->begin = (char*) (array->array + index);

  mk_data_content(n, array->bucket);

  array->bucket->region->begin = begin;

  if ( array->index < index ) ++array->index; // novo item em uma posicao aleatoria 

  return array;  
}

ArrayList* array_list_add_int_on(ArrayList* array, size_t index, int n) {
  char* begin                  = array->bucket->region->begin;

  array->bucket->region->begin = (char*) (array->array + index);

  mk_int_content(n, array->bucket);

  array->bucket->region->begin = begin;

  return array;  
}

Data* array_list_getitem(ArrayList* array, size_t index) {
  if (index > array->index) return NULL;

  return array->array + index;
}
