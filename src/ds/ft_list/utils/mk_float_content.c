#include "../linked.h"

Data * mk_float_content(float content, void (*ffree)(void *)) 
{
  float *new_float;
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), NULL);

  if (!data)
    return (NULL);

  new_float = (float *) ft_calloc(1, sizeof(float), NULL);

  if (!new_float) 
  {
    free(data);
    return (NULL);
  }
  *new_float = content;
  data->content = (void *) new_float;
  data->type = FLOAT;
  data->ffree = ffree;


  return (data);
}
