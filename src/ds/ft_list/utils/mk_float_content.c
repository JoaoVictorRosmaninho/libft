#include "../../../../includes/libft.h"

Data * mk_float_content(float content, t_coliseu* coliseu) 
{
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);

  data->content.f = content;
  data->content_type      = FLOAT;

  return (data);
}
