


#include "./libft.h"

size_t ft_strlcpy(char *dst, const char *src, size_t size) 
{
        size_t len_src; 

	if (!dst || !src)
          return (0); 
        len_src = ft_strlen(src);  
	if (size < 1)
		return (len_src);
        ft_memcpy(dst, src, (size - 1));
        dst[size - 1] = '\0'; 
	return (len_src);  
} 
