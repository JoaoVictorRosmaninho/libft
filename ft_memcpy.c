#include "./libft.h"

void *ft_memcpy(void *TO, const void *FROM, size_t size) 
{
  size_t index; 

  if (!TO || !FROM)
    return (NULL);  
  index = 0; 
  while (index < size) 
  {
    *(((unsigned char *) TO) + index) =  *(((unsigned char *) FROM) + index);
    index++;
  }
  return (TO); 
}
