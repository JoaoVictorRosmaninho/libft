#include "../linked.h"

Data * mk_double_content(double content, void (*ffree)(void *)) 
{
  double *new_double;
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data));

  if (!data)
    return (NULL);

  new_double = (double *) ft_calloc(1, sizeof(double));

  if (!new_double) 
  {
    free(data);
    return (NULL);
  }
  *new_double = content;
  data->content = (void *) new_double;
  data->type = DOUBLE;
  data->ffree = ffree;


  return (data);
}
