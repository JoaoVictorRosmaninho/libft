#include "./libft.h"
#include <stdio.h>

char *ft_strtrim(char const *s1, char const *set)
{
  size_t size; 
  unsigned int ini;
  char *newstring;


  ini = 0;

  if (!s1 || !set)
     return (NULL);
   while(s1[ini] && ft_strchr(set, s1[ini]))
     ini++;
   size = ft_strlen(s1) - 1; 
   while(size && ft_strchr(set, s1[size]))
     size--;
   newstring = ft_substr(s1, ini, (size - ini + 1));
   return (newstring);
}

