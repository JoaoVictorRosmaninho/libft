#include "./libft.h"

void ft_lstclear(t_list **lst, void (*del)(void*)) {
 t_list *node; 
 t_list *tmp; 

 if (!lst)
   return ;
 node = *lst; 
 while (node != NULL) 
 {
    tmp = node; 
    del(node->content);     
    node = node->next; 
    free(tmp); 
 }
 *lst = NULL; 
}
