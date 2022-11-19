#include "./libft.h"


t_node *ft_lstpop(t_list *list, unsigned int at)
{
  unsigned int i;
  t_node *node;

  i = 0;
  node = list->head;

  while (i < at) 
  {
    node = node->next;
    i++; 
  }

  /*  adjusting nodes  */
  if (!i) {
    list->head = node->next; 
    list->head->prev = NULL;
  } else {
    node->prev->next = node->next; 
    node->next->prev = node->prev;
  }
  node->prev = NULL;
  node->next = NULL;
  return (node);
}
