#include "./libft.h"
void *ft_bzero(void *BLOCK, size_t SIZE) {
  size_t index; 

  index = 0; 
  while (index < SIZE) {
    *(((unsigned char *) BLOCK) + index) = 0; 
    index++;
  }
  return (BLOCK);
} 
