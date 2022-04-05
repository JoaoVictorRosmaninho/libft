#include "./libft.h"

void *ft_calloc(size_t COUNT, size_t ELTSIZE) {
  void *ptr; 

  ptr = malloc(COUNT * ELTSIZE); 
  ft_bzero(ptr, COUNT * ELTSIZE);
  return (ptr); 
}
