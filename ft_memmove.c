#include "./libft.h"

void *ft_memmove(void *dest, const void *src, size_t n) 
{
  unsigned char *d; 
  const unsigned char *s; 
  
  if (!dest || !src)
    return (NULL);
  d = (unsigned char *) dest; 
  s = (unsigned char *) src; 

  if (dest > src) {
    while (n--)
      d[n] = s[n];
  } else {
    ft_memcpy(dest, src, n);
  }
  return (dest);  
} 
