
#include "./libft.h"

char *ft_strchr(const char *STRING, int C)
{
  unsigned int index; 

  index = 0; 
  while (STRING[index]) {
    if ((unsigned char ) STRING[index] == (unsigned char ) C)
      return (((char *) STRING) + index); 
    index++;
  }
  return (NULL); 
}

