#include "../../../../includes/libft.h"

Data * mk_generic_content(void *content, t_coliseu* coliseu) 
{
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);

  data->content = content;
  data->type = POINTER;

  return (data);
}
