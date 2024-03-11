

#include "../../../../includes/libft.h"

t_node *ft_lstitem(t_list *lst, unsigned int at) 
{
  unsigned int i;
  t_node *node;

  i = 0;
  node = lst->head;

  while(i < at && node != NULL) 
  {
    i++;
    node = node->next;
  }
  return (node);
}
