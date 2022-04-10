#include "./libft.h"

int ft_memcmp(const void *A1, const void *A2, size_t SIZE) {
  size_t index;
  unsigned char *a1;
  unsigned char *a2; 

  if (!A1 || !A2)
    return (0);
  index = 0;
  a1 = (unsigned char *) A1; 
  a2 = (unsigned char *) A2; 
  while (index < SIZE) {
    if (a1[index] != a2[index]) {
      if (a1[index] < a2[index])
        return (-1); 
      return ((int) (a2 - a1));
    }
    index++;
  }
  return (0);
} 

