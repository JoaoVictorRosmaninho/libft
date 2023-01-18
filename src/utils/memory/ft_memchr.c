/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:20:19 by jv                #+#    #+#             */
/*   Updated: 2022/06/26 00:05:53 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	*ft_memchr(const void *BLOCK, int C, size_t SIZE)
{
	unsigned char	*ptr;
	unsigned char	ch;

	ptr = (unsigned char *) BLOCK;
	ch = (unsigned char) C;
	while (SIZE)
	{
		if (*ptr == ch)
			return (ptr);
		SIZE--;
		ptr++;
	}
	return (NULL);
}
