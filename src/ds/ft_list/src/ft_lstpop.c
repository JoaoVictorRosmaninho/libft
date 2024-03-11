#include "../../../../includes/libft.h"


t_node *ft_lstpop(t_list *list, unsigned int at)
{
  unsigned int i;
  t_node *node;

  if (!list || !list->head)
    return (NULL);

  i = 0;
  node = list->head;

  while (i < at && node != NULL) 
  {
    node = node->next;
    i++; 
  }

  /*  adjusting nodes  */
  if (!i) {
    list->head = node->next; 
    if (list->head)
      list->head->prev = NULL;
    else {
      list->tail = NULL;
    }
  } else {
    node->prev->next = node->next;
    if (node->next)
      node->next->prev = node->prev; 
  }
  node->prev = NULL;
  node->next = NULL;
  list->size--;
  return (node);
}
