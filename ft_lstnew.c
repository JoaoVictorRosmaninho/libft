#include "./libft.h"

t_list *ft_lstnew(void *content) {
   t_list *node; 

   if (!(node = (t_list *)ft_calloc(1, sizeof(t_list))))
     return (NULL); 
   node->content = content;
   node->next = NULL;
   return (node); 
}
