/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:59:00 by jv                #+#    #+#             */
/*   Updated: 2022/04/10 14:59:42 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strchr(const char *STRING, int C)
{
	size_t	index;

	if (!STRING)
		return (NULL);
	index = 0;
	while (STRING[index])
	{
		if ((unsigned char ) STRING[index] == (unsigned char ) C)
			return (((char *) STRING) + index);
		index++;
	}
	return (NULL);
}
