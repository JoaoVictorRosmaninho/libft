
#include "../../../includes/libft.h"


void array_list_print(ArrayList* arraylist) {
  ft_printf("[");
  for( size_t i = 0; i < arraylist->index; i++) {
    switch (arraylist->array[i].type) 
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



ArrayList   array_list_init( size_t capacity ) {
    t_coliseu* coliseu_array = ft_coliseu_create_on_arena( capacity * sizeof(Data) );

    ArrayList array =  {
        .bucket =  coliseu_array,
        .array        =  (Data*)coliseu_array->region->begin,
        .capacity     =  capacity,
        .index        =  0
    };

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
     ft_coliseu_rollback(array->bucket->region, sizeof(Data*));
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

Data* array_list_getitem(ArrayList* array, size_t index) {
  if (index > array->capacity) return NULL;

  return array->array + index;
}
