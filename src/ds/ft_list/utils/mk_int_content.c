#include "../../../../includes/libft.h"

Data * mk_int_content(int content, t_coliseu* coliseu) 
{
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);

  
  data->content.i  = content;
  data->type       = INTEGER;

  return (data);
}
