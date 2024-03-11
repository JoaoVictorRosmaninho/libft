#include "../../../../includes/libft.h"

t_list *ft_lstnew(t_coliseu* coliseu) {
  t_list *new_list;


  new_list = (t_list *) ft_calloc(1, sizeof(t_list), coliseu);
  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->size = 0;

  return (new_list);
}
