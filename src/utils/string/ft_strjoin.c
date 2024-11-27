/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:03:59 by jv                #+#    #+#             */
/*   Updated: 2024/11/22 20:51:25 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2, t_coliseu* coliseu)
{
	size_t	size;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);

	size    = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *) ft_calloc(size, sizeof(char), coliseu);

	if (!new_str) return (NULL);
	
	ft_strlcat(new_str, s1, size);
	ft_strlcat(new_str, s2, size);
	return (new_str);
}
