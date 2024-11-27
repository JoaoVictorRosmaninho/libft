#include "../../../../includes/libft.h"

Data * mk_string_content(char *content,  t_coliseu* coliseu) 
{
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);

  data->content.s = content;
  data->content_type      = STRING;

  return (data);
}
