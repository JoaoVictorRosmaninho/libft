#include "../../../../includes/libft.h"


static void split_list(t_node **a, t_node **b, t_node *source) {
  /* fast and lower strategy  */
  t_node *s;
  t_node *f;

  s = source;
  f = source->next;

  while (f != NULL) {
     f = f->next;
     if (f != NULL) {
       s = s->next;
       f = f->next;
     }
  }
  /* s está antes do ponto medio da lista  */
  *a = source;
  *b  = s->next; // ponto medio
   s->next = NULL; //debugar
}


static t_node *merge(t_node *a, t_node *b) {
  t_node *result;

  result = NULL;

  if (a == NULL)
    return (b);
  else if (b == NULL)
    return (a);
  
  int ac = *(int *) a->content;
  int bc = *(int *) b->content;
  if ( ac <= bc ) {
    result = a;
    result->next = merge(a->next, b);
    result->next->prev = result;
  } else {
    result = b;
    result->next = merge(a, b->next);
    result->next->prev = result;
  }
  return (result);
}

static void msort(t_node **node) {
  t_node *head = *node;
  t_node *a;
  t_node *b;

  /* base case, retorne se nao tiver como dividir mais  */
  if (!head || !head->next)
    return;

  /* quebrar a lista em lista menores  */
  split_list(&a, &b, head);

  /* recursao para quebrar as sublistas  */
  msort(&a);
  msort(&b);

  *node = merge(a, b);
}

void ft_mlsort(t_list *lst) {
    msort(&lst->head);
}
