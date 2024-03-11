#include "../../../../includes/libft.h"

Data * mk_int_content(int content, t_coliseu* coliseu) 
{
  int *new_int;
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);

  new_int = (int *) ft_calloc(1, sizeof(int), coliseu);

  if (!new_int) 
  {
    free(data);
    return (NULL);
  }
  *new_int = content;
  data->content = (void *) new_int;
  data->type = INTEGER;

  return (data);
}
