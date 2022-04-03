#include "./libft.h"



char *ft_strnstr(const char *big, const char *little, size_t len) 
{
  size_t index;
  size_t size; 

  index = 0;
  size = ft_strlen(little);
  if (*little == '\0')
   return ((char *) big);
  while (index < len) {
    if (*little == big[index]) {
      if ((index + size + 1) > len) 
        break; 
      if (ft_strncmp(big, little, size) == 0)
        return ((char *) (big + index)); 
    }
    index++;
  }
  return (NULL);
}
