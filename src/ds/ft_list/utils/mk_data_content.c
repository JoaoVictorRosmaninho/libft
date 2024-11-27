#include "../../../../includes/libft.h"

Data * mk_data_content(Data* content, t_coliseu* coliseu) 
{
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);


  ft_memcpy(data, content, sizeof(Data));

 // if (data->content.s && coliseu->neasted) data->content.s = ft_strdup(data->content.s, coliseu->neasted);

  data->content_type = POINTER;

  return (data);
}
