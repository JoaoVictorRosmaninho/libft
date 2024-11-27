#include "../../../../includes/libft.h"


void ft_lstprint(t_list *lst) {
  t_node *head;

  head = lst->head;

  ft_printf("[");
  while (head != NULL) {
    switch (head->data->content_type) 
    {
      case STRING:
        ft_printf("%s", head->data->content.s);
      break;
      case INTEGER:
        ft_printf("%d", head->data->content.i);
      break;
      case FLOAT:
        ft_printf("%f", head->data->content.f);
      break;
      case DOUBLE:
        ft_printf("%f", head->data->content.d);
      break;
      case CHAR:
        ft_printf("%c", head->data->content.c);
      break;
      default:
        ft_printf("%p", head->data->content.p);
      break;
    }
    if (head->next != NULL)
      ft_printf(", ");

    head = head->next;
  }
  ft_printf("]\n");
}
