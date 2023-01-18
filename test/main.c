#include "../includes/libft.h"


int main(void) {
  t_list *list = ft_lstnew();

  ft_lstadd_back(list, ft_lstnew_node(mk_string_content("joao victor")));
  ft_lstadd_back(list, ft_lstnew_node(mk_string_content("pedro henrrique")));
  ft_lstadd_back(list, ft_lstnew_node(mk_int_content(15)));

  ft_lstprint(list);
  ft_lst_mv_next_to_front(list, list->tail->prev->prev);
  ft_lstprint(list);
  ft_lstclear(list, NULL);
  free(list);
}
