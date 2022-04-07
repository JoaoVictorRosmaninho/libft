#include "./libft.h"
#include <bsd/string.h>
char *ft_substr(char const *s, unsigned int start, size_t len) {
  size_t len_str; 
  char *sub_str; 

  if (!s)
    return (NULL); 
  len_str = ft_strlen(s);
  if ((start + len) > len_str) 
    NULL;
  if ((sub_str = (char *) malloc(len + 1)) == NULL)
    return (NULL);
  ft_strlcpy(sub_str, (s + start), (len + 1));
  return (sub_str); 
} 
