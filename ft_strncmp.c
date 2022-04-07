#include "./libft.h"

int ft_strncmp(const char *S1, const char *S2, size_t SIZE)
{
  size_t i; 

  if (!S1 || !S2 || !SIZE)
    return (0); 
  i = 0;
  while ((S1[i] == S2[i]) && S1[i] && S2[i] && (i < (SIZE - 1)))
    i++;
  return ((int)S1[i] - (int)S2[i]);  
}
