#ifndef LINKED_H
# define LINKED_H
# include <stdlib.h>
# include "../../../includes/libft.h"

  typedef enum {
    STRING,
    DOUBLE,
    INTEGER,
    CHAR,
    FLOAT
  } DataType;

  typedef struct t_data {
    void *content;
    DataType type;
  } Data;

  typedef struct s_node
  {
    struct s_node	*next;
    struct s_node *prev;
    Data *data;
  }	t_node;

  typedef struct {
      t_node *head;
      t_node *tail;
      unsigned int size;
  } t_list;


  Data *mk_string_content(char *content);

  Data *mk_int_content(int content);

  Data *mk_double_content(double content);

  Data *mk_float_content(float content);

  Data *mk_char_content(char content);


  t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

  t_list    *ft_lstnew(void);

  void		ft_lstadd_front(t_list *lst, t_node *new);

  void		ft_lstadd_back(t_list *lst, t_node *new);

  void		ft_lstdelone(t_node *node, void (*del)(void*));

  void		ft_lstclear(t_list *lst, void (*del)(void*));

  void		ft_lstiter(t_list *lst, void (*f)(void *));

  void    ft_lstprint(t_list *lst);

  void    ft_mlsort(t_list *lst);

  void    ft_lst_mv_next_to_front(t_list *lst, t_node * node);

  t_node  *ft_lstpop(t_list *lst, unsigned int at);

  t_node		*ft_lstnew_node(Data *data);

  t_node  *ft_lstpop_head(t_list *lst);

  t_node  *ft_lstitem(t_list *lst, unsigned int at);
  
#endif


