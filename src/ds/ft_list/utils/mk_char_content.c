#include "../../../../includes/libft.h"

Data * mk_char_content(char content, t_coliseu* coliseu) 
{
  char *new_char;
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data), coliseu);

  if (!data)
    return (NULL);

  new_char = (char *) ft_calloc(1, sizeof(char), coliseu);

  if (!new_char) 
  {
    free(data);
    return (NULL);
  }
  *new_char = content;
  data->content = (void *) new_char;
  data->type = CHAR;

  return (data);
}
