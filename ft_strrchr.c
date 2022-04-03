#include "./libft.h"

char *ft_strrchr(const char *STRING, int C) {
  size_t size; 

  size = ft_strlen(STRING);
  while (size > 0) {
    if ((unsigned char ) STRING[size] == (unsigned char) C)
      return ((char *) (STRING + size));
    size--;
  }
  return (NULL); 
}
