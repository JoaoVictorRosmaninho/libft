#include "../../../../includes/libft.h"

Data * mk_double_content(double content, t_coliseu* coliseu) 
{
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);


  data->content.d = content;
  data->type      = DOUBLE;

  return (data);
}
