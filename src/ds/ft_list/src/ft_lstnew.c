#include "../linked.h"

t_list *ft_lstnew(void) {
  t_list *new_list;


  new_list = (t_list *) ft_calloc(1, sizeof(t_list), NULL);
  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->size = 0;

  return (new_list);
}
