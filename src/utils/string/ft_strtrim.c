/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:47:35 by jv                #+#    #+#             */
/*   Updated: 2024/04/06 12:49:42 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	ini;
	size_t			size;

	ini = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[ini] && ft_strchr(set, s1[ini]))
		ini++;
	size = ft_strlen(s1);
	while (size && ft_strchr(set, s1[size]))
		size--;
	if ((size - ini + 1) < 1)
		return (ft_strdup(""));
	return (ft_substr(s1, ini, (size - ini + 1)));
}
