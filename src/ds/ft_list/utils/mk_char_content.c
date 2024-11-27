#include "../../../../includes/libft.h"

Data * mk_char_content(char content, t_coliseu* coliseu) 
{
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);

  data->content.c = content;
  data->content_type = CHAR;

  return (data);
}
