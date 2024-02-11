#include "../linked.h"

Data * mk_generic_content(void *content, void (*ffree)(void *)) 
{
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data));

  if (!data)
    return (NULL);

  data->content = content;
  data->type = POINTER;
  data->ffree = ffree;

  return (data);
}
