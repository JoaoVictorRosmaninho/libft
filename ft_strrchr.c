/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:13 by jv                #+#    #+#             */
/*   Updated: 2022/04/24 14:39:15 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strrchr(const char *STRING, int C)
{
	int	size;

	size = ft_strlen(STRING);
	while (size >= 0)
	{
		if ((unsigned char) STRING[size] == (unsigned char) C)
			return ((char *)(STRING + size));
		size--;
	}
	return (NULL);
}
