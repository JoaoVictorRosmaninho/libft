#include "../../../../includes/libft.h"

Data * mk_float_content(float content, t_coliseu* coliseu) 
{
  float *new_float;
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);

  new_float = (float *) ft_calloc(1, sizeof(float), coliseu);

  if (!new_float) 
  {
    free(data);
    return (NULL);
  }
  *new_float = content;
  data->content = (void *) new_float;
  data->type = FLOAT;


  return (data);
}
