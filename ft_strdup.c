#include "./libft.h"

char *ft_strdup(const char *str) 
{
  char *new_str; 
  size_t size_buffer;

  if (!str)
    return (NULL); 
  size_buffer = ft_strlen(str) + 1;
  new_str = (char *) malloc(size_buffer); 
  ft_strlcpy(new_str, str, size_buffer); 
  return (new_str);
}



