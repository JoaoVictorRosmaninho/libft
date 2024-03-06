#include "../linked.h"

Data * mk_int_content(int content, void (*ffree)(void *)) 
{
  int *new_int;
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), NULL);

  if (!data)
    return (NULL);

  new_int = (int *) ft_calloc(1, sizeof(int), NULL);

  if (!new_int) 
  {
    free(data);
    return (NULL);
  }
  *new_int = content;
  data->content = (void *) new_int;
  data->type = INTEGER;
  data->ffree = ffree;

  return (data);
}
