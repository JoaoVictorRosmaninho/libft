#include "./libft.h"



unsigned int ft_lstsize(t_list *lst) 
{
  t_node *head;
  unsigned int size;

  head = lst->head;
  size = 0;

  while (head) {
    head = head->next;
    size++;
  }
  return (size);
}
