
#include "./libft.h"

char *ft_strchr(const char *STRING, int C)
{
  size_t index; 

  if (!STRING)
    return (NULL); 
  index = 0; 
  while (STRING[index]) {
    if ((unsigned char ) STRING[index] == (unsigned char ) C)
      return (((char *) STRING) + index); 
    index++;
  }
  return (NULL); 
}

