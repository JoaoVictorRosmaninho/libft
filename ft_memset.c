#include "./libft.h"
void *ft_memset(void *BLOCK, int C, size_t SIZE) {
  unsigned char value; 
  size_t index; 

  value = (unsigned char) C; 
  index = 0; 
  while (index < SIZE) {
    *(((unsigned char *) BLOCK) + index) = value; 
    index++;
  }
  return (BLOCK);
} 
