#include "./libft.h"
#include <stdio.h>

static unsigned int ft_countChar(const char *s, char c) {
   unsigned int delimiter; 
   unsigned int index; 

   delimiter = 0;
   index = 0;
   while(s[index]) {
     if (s[index] == c)
       delimiter++;
     index++;
   }
   return (delimiter);
}


char **ft_split(const char *s, char c) {
  char **bipointer; 
  unsigned int delimiters; 
  unsigned int ini; 
  unsigned int end; 
  unsigned int index; 

  if (!s)
    return (NULL); 
  delimiters = ft_countChar(s, c) + 1;
  ini = 0;
  end = 0;
  index = 0; 
  if ((bipointer = (char **) ft_calloc(delimiters + 1, sizeof(char *))) == NULL)
    return (NULL);
  while(s[end]) 
  {
    if (s[end] == c)
    {
      bipointer[index++] = ft_substr(s, ini, (end - ini));
      ini = end + 1;
    }
    end++;
  }
  bipointer[index++] = ft_substr(s, ini, (end - ini));
  bipointer[index] = NULL; 
  return (bipointer);
}
