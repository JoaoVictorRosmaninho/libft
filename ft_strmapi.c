#include "./libft.h"

char *ft_strmapi(char const *s, char (*f)(unsigned int, char)) {
  unsigned int index;
  char *new_str;
  
  if (!s || !f)
    return (NULL);
  new_str = (char * )ft_calloc(ft_strlen(s) + 1, sizeof(char));
  if (!new_str) 
    return (NULL);
  while (s[index])
  {
    new_str[index] = f(index, s[index]); 
    index++;
  }
  return (new_str);  
}
