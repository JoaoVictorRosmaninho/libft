#ifndef LINKED_H
# define LINKED_H
# include <stdlib.h>


  typedef enum {
    STRING,
    DOUBLE,
    INTEGER,
    CHAR,
    FLOAT,
    POINTER,
    DATA
  } DataType;

  typedef struct t_data {
    union {
      double         d;
      int            i;
      unsigned  int  ui;
      float          f;
      char*          s;
      void*          p;
      char           c;
    } content;
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

  typedef struct  {
    t_coliseu* bucket;
    Data*      array;
    size_t     capacity;
    size_t     index;
 } ArrayList;


  /* ArrayListAPi*/

  # define array_list_add(array, item) _Generic((item), \
           int:   array_list_add_int,   char*: array_list_add_str, \
           float: array_list_add_float, double: array_list_add_double, \
           Data*: array_list_add_data)(array, item)
  
  # define array_list_add_on(array, index, item) _Generic((item), \
           int:   array_list_add_int_on,   char*: array_list_add_str_on, \
           float: array_list_add_float_on, double: array_list_add_double_on, \
           Data*: array_list_add_data_on)(array, index, item)


  ArrayList   array_list_init( size_t capacity );

  ArrayList*  array_list_init_on_buffer( size_t capacity );

  ArrayList*  array_list_add_int_on(ArrayList* array, size_t index, int n);

  ArrayList*  array_list_add_str_on(ArrayList* array, size_t index, char* n);

  ArrayList*  array_list_add_float_on(ArrayList* array, size_t index, float n);

  ArrayList*  array_list_add_double_on(ArrayList* array, size_t index, double n);

  ArrayList*  array_list_add_data_on(ArrayList* array, size_t index, Data* n);
  
  ArrayList*  array_list_add_int(ArrayList* array, int n);

  ArrayList*  array_list_add_float(ArrayList* array, float n);

  ArrayList*  array_list_add_data(ArrayList* array, Data* n);

  ArrayList*  array_list_add_str(ArrayList* array, char* string);

  ArrayList*  array_list_add_double(ArrayList* array, double n) ;

  ArrayList*  array_list_pop( ArrayList* array );

  void        array_list_deinit( ArrayList* array );

  Data*       array_list_getitem(ArrayList* array, size_t index);

  void array_list_print(ArrayList* arraylist);



  /* LinkedListApi */

  Data *mk_string_content(char *content, t_coliseu* coliseu);

  Data *mk_int_content(int content, t_coliseu* coliseu);

  Data *mk_double_content(double content, t_coliseu* coliseu);

  Data *mk_float_content(float content, t_coliseu* coliseu);

  Data *mk_char_content(char content, t_coliseu* coliseu);

  Data *mk_generic_content(void *content, t_coliseu* coliseu);


  t_list	*ft_lstmap(t_list *lst, void *(*f)(void *,  t_coliseu*), t_coliseu* coliseu);

  t_list  *ft_lstnew(t_coliseu* coliseu);


  void    ft_lst_for_each(t_list *lst, void (*f)(void *));

  void		ft_lstadd_front(t_list *lst, t_node *new);

  void		ft_lstadd_back(t_list *lst, t_node *new);

  void		ft_lstdelone(t_node *node);

  void		ft_lstclear(t_list *lst);

  void		ft_lstiter(t_list *lst, void (*f)(void *));

/* passar uma função de exibição para cada indice */
/* Uma função que seria similar ao metodo ToString do java  */
  void    ft_lstprint(t_list *lst);

  void    ft_mlsort(t_list *lst);

  void    ft_lst_mv_next_to_front(t_list *lst, t_node * node);

  void    ft_lstpop_tail(t_list *lst);

  void    ft_lst_remove_node(t_list* lst, t_node* node);

  t_node  *ft_lstpop(t_list *lst, unsigned int at);

  t_node		*ft_lstnew_node(void *data, DataType type, t_coliseu* coliseu);

  t_node  *ft_lstpop_head(t_list *lst);

  t_node  *ft_lstitem(t_list *lst, unsigned int at);
  
  t_node* ft_lst_include(t_list *lst, void* item, uint8_t (*f)(void*, void*));

  uint8_t ft_lst_search_and_pop(t_list *lst, void* item, uint8_t (*f)(void*, void*));

#endif


