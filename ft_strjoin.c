#include "./libft.h"
#include <bsd/string.h>

char *ft_strjoin(char const *s1, char const *s2) {
  size_t size; 
  char *new_str;

  if (!s1 || !s2)
    return (NULL);
  size = ft_strlen(s1) + ft_strlen(s2) + 1; 
  if ((new_str = (char *) ft_calloc(size, 1)) == NULL)
    return (NULL);
  ft_strlcat(new_str, s1, size); 
  ft_strlcat(new_str, s2, size); 
  return (new_str); 
}
