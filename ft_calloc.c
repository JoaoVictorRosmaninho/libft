#include "./libft.h"

void *ft_calloc(size_t COUNT, size_t ELTSIZE) {
  void *ptr; 

  if ((ptr = malloc(COUNT * ELTSIZE)) == NULL)
    return (NULL); 
  ft_bzero(ptr, COUNT * ELTSIZE);
  return (ptr); 
}
