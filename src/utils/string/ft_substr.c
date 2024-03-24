/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:50:49 by jv                #+#    #+#             */
/*   Updated: 2024/03/23 15:58:13 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_str;
	char	*sub_str;

	if (!s)
		return (NULL);
	len_str = ft_strlen(s);
	if (start > len_str)
		return (NULL);
	if ((start + len) > len_str)
		NULL;
	sub_str = (char *) malloc(len + 1);
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, (s + start), (len + 1));
	return (sub_str);
}
