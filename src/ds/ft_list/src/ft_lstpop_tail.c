#include "../../../../includes/libft.h"

void ft_lstpop_tail(t_list *lst) 
{
    if (!lst)
      return ;
    if (!lst->tail)
      return;
    if (lst->tail == lst->head)
      return;
    
    t_node *prev = lst->tail->prev;
    prev->next = NULL;
    free(lst->tail);
    lst->tail = prev;
}
