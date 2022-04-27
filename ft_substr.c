/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:50:49 by jv                #+#    #+#             */
/*   Updated: 2022/04/26 22:03:13 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_str;
	size_t	size;
	char	*sub_str;

	if (!s)
		return (NULL);
	len_str = ft_strlen(s);
	if (start > len_str)
		return (ft_strdup(""));
	if (len_str - start > len)
		size = len + 1;
	else
		size = len_str - start + 1;
	sub_str = (char *) malloc(sizeof(char) * size);
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, (s + start), (len + 1));
	return (sub_str);
}
