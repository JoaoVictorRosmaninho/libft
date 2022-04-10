#include "./libft.h"
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)) {

  t_list *new_list;
  t_list *node; 
  
  if (!lst)
    return (NULL);

  new_list = NULL; 
  while (lst != NULL)
  {
    if (!(node = ft_lstnew(f(lst->content))))
    {
       ft_lstclear(&node, del);
       return (NULL); 
    }
    ft_lstadd_back(&new_list, node);
    lst = lst->next; 
  }
  return (new_list); 
}
