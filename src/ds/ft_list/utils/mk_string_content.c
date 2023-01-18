#include "../linked.h"

Data * mk_string_content(char *content) 
{
  size_t size;
  char *new_str;
  Data *data;
  
  size = ft_strlen(content) + 1;

  data = (Data *) ft_calloc(1, sizeof(Data));

  if (!data)
    return (NULL);

  new_str = (char *) ft_calloc(size, sizeof(char));

  if (!new_str) 
  {
    free(data);
    return (NULL);
  }

  ft_memcpy(new_str, content, size);
  data->content = new_str;
  data->type = STRING;

  return (data);
}
