/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:09:01 by jv                #+#    #+#             */
/*   Updated: 2022/04/10 16:12:57 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	size_t	size;

	index = 0;
	size = ft_strlen(little);
	if (*little == '\0')
		return ((char *) big);
	if (!big || !len)
		return (NULL);
	while (index < len)
	{
		if (*little == big[index])
		{
			if ((index + size + 1) > len)
				break ;
			if (ft_strncmp((big + index), little, size) == 0)
				return ((char *)(big + index));
		}
		index++;
	}
	return (NULL);
}
