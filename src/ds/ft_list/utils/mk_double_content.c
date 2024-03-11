#include "../../../../includes/libft.h"

Data * mk_double_content(double content, t_coliseu* coliseu) 
{
  double *new_double;
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);

  new_double = (double *) ft_calloc(1, sizeof(double), coliseu);

  if (!new_double) 
  {
    free(data);
    return (NULL);
  }
  *new_double = content;
  data->content = (void *) new_double;
  data->type = DOUBLE;

  return (data);
}
