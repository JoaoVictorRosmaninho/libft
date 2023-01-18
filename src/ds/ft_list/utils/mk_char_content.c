#include "../linked.h"

Data * mk_char_content(char content) 
{
  char *new_char;
  Data *data;
  
  data = (Data *) ft_calloc(1, sizeof(Data));

  if (!data)
    return (NULL);

  new_char = (char *) ft_calloc(1, sizeof(char));

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
