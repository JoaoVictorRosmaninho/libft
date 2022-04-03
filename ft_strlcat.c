#include "./libft.h"

size_t ft_strlcat(char *dst, const char *src, size_t size)
{
        size_t	src_size;
	size_t	dst_size;
	size_t	i;

	src_size = ft_strlen(src);
	dst_size = ft_strlen(dst);
	i = 0;
	if (size <= dst_size)
		return (size + src_size);
	while (src[i] && ((i + dst_size) < (size - 1)))
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (src_size + dst_size);
}
 