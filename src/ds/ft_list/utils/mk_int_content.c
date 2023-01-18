#include "../linked.h"

Data * mk_int_content(int content) 
{
  int *new_int;
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data));

  if (!data)
    return (NULL);

  new_int = (int *) ft_calloc(1, sizeof(int));

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
