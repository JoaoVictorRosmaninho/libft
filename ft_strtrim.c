/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:47:35 by jv                #+#    #+#             */
/*   Updated: 2022/04/10 15:50:37 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	ini;
	size_t			size;
	char			*newstring;

	ini = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[ini] && ft_strchr(set, s1[ini]))
		ini++;
	size = ft_strlen(s1) - 1;
	while (size && ft_strchr(set, s1[size]))
		size--;
	newstring = ft_substr(s1, ini, (size - ini + 1));
	return (newstring);
}
