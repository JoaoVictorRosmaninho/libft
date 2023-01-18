/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:16:13 by jv                #+#    #+#             */
/*   Updated: 2022/04/21 13:40:43 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

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
