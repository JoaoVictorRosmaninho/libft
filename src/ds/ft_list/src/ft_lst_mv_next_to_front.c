#include "../../../../includes/libft.h"


void ft_lst_mv_next_to_front(t_list *lst, t_node *node) {
  t_node *next;
  t_node *tmp;

  if (!lst || !node)
    return ;
  next = node->next;
  node->next = NULL;

  if (!next)
    next = node;
  

  tmp = lst->head;

  next->prev = NULL;
  lst->head = next;
  
  tmp->prev = lst->tail;
  lst->tail->next = tmp;

  lst->tail = node;
}
