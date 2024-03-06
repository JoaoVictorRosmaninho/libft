#include "../../../includes/libft.h"

char	*ft_strndup(const char *str, unsigned int n)
{
	char	*new;

	new = NULL;
	new = ft_calloc(sizeof(char), n + 1, NULL);
	ft_strlcpy(new, str, n + 1);
	return (new);
}

