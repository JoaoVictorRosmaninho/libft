#include "../../../../includes/libft.h"


void ft_lstprint(t_list *lst) {
  t_node *head;

  head = lst->head;

  ft_printf("[");
  while (head != NULL) {
    switch (head->data->type) 
    {
      case STRING:
        ft_printf("%s", (char *) head->data->content);
      break;
      case INTEGER:
        ft_printf("%d", *(int *) head->data->content);
      break;
      case FLOAT:
        ft_printf("%f", *(float *) head->data->content);
      break;
      case DOUBLE:
        ft_printf("%f", *(double *) head->data->content);
      break;
      case CHAR:
        ft_printf("%c", *(char *) head->data->content);
      break;
      default:
        ft_printf("%p", head->data->content);
      break;
    }
    if (head->next != NULL)
      ft_printf(", ");

    head = head->next;
  }
  ft_printf("]\n");
}
