#include "./libft.h"


size_t ft_strlen(const char *S) {
  size_t size; 

  size = 0; 
  while (S[size])
    size++; 
  return (size); 
}
